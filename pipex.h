/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorcher <mcorcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 05:55:57 by mcorcher          #+#    #+#             */
/*   Updated: 2025/05/19 05:56:47 by mcorcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../Cursus/ft_printf/ft_printf.h"
# include "../Cursus/libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipexcmd
{
	pid_t				pid1;
	pid_t				pid2;
	int					tube[2];
	int					infile;
	int					outfile;
	char				*infile_path;
	char				*outfile_path;
	char				**cmds;
	int					argc;
	int					status;
	struct s_pipexcmd	*nextnode;
}						t_pipexcmd;

t_pipexcmd				*parsing_arg_initialize(void);
t_pipexcmd				*crea_comando(char *cmd);
t_pipexcmd				*parsear_entrada(int argc, char **argv);
t_pipexcmd				*parsing_arg(int argc, char **argv);
t_pipexcmd				*initialize_head(int argc, char **argv);
t_pipexcmd				*add_commands_to_list(int argc, char **argv,
							t_pipexcmd *head);
void					free_command_list(t_pipexcmd *head);
char					*get_path(char **envp);
char					*find_path(char *cmd, char **envp);

void					ft_error(void);
void					execute(t_pipexcmd *cmds, char **envp);
void					execute_cmd(t_pipexcmd *cmd, char **envp);
void					open_input_file(t_pipexcmd *cmds);
void					process_commands(t_pipexcmd *cmds, t_pipexcmd *current,
							int *fd_prepipe, char **envp);
void					create_pipe(t_pipexcmd *current);
void					child_process(t_pipexcmd *cmds, t_pipexcmd *current,
							int fd_prepipe, char **envp);
void					setup_input(t_pipexcmd *cmds, t_pipexcmd *current,
							int fd_prepipe);
void					setup_output(t_pipexcmd *cmds, t_pipexcmd *current);
void					parent_process(t_pipexcmd *current, int *fd_prepipe);
void					wait_for_processes(t_pipexcmd *cmds);

#endif