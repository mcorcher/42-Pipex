/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorcher <mcorcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:32:03 by mcorcher          #+#    #+#             */
/*   Updated: 2025/05/18 19:16:38 by mcorcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../Cursus/ft_printf/ft_printf.h"
# include "../Cursus/libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipexcmd
{
	pid_t pid1;                  // pid from the 1º process
	pid_t pid2;                  // pid from the 2º process
	int tube[2];                 // pipe with 2 pos. 1 read fd 2. write fd
	int infile;                  // fd for the infile (open and read file)
	int outfile;                 // fd for the outfile (open and write file)
	char **cmds;                 // array for each cmd and their args
	int argc;                    // Nmb of args of our cmds
	int status;                  // checks if there is a cmd ex.
	struct s_pipexcmd *nextnode; // pointer to next node
}			t_pipexcmd;

// Function prototypes
t_pipexcmd	*parsing_arg(int argc, char **argv);
t_pipexcmd	*parsear_entrada(int argc, char **argv);
t_pipexcmd	*parsing_arg_initialize(void);
t_pipexcmd	*crea_comando(char *cmd);
void		free_cmd_list(t_pipexcmd *head);
char		*get_path(char **envp);
char		*find_path(char *cmd, char **envp);
void		free_paths(char **paths);
char		*build_valid_path(char **paths, char *cmd);
void		ft_error(void);
void		execute(t_pipexcmd *cmds, char **envp);
void		execute_cmd(t_pipexcmd *cmd, char **envp);
void		open_input_file(t_pipexcmd *cmds);
void		process_commands(t_pipexcmd *cmds, t_pipexcmd *current,
			int *fd_prepipe, char **envp);
void		create_pipe(t_pipexcmd *current);
void		child_process(t_pipexcmd *cmds, t_pipexcmd *current, int fd_prepipe,
			char **envp);
void		setup_input(t_pipexcmd *cmds, t_pipexcmd *current, int fd_prepipe);
void		setup_output(t_pipexcmd *cmds, t_pipexcmd *current);
void		parent_process(t_pipexcmd *current, int *fd_prepipe);
void		wait_for_processes(t_pipexcmd *cmds);
t_pipexcmd	*init_head_node(char *infile, char *outfile);
int	add_command_nodes(t_pipexcmd *head, int argc, char **argv);

#endif
