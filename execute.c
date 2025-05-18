/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorcher <mcorcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:31:16 by mcorcher          #+#    #+#             */
/*   Updated: 2025/05/18 18:51:50 by mcorcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_cmd(t_pipexcmd *cmd, char **envp)
{
	char	*path;

	path = find_path(cmd->cmds[0], envp);
	if (!path)
	{
		ft_printf("Command not found: %s\n", cmd->cmds[0]);
		exit(127);
	}
	if (execve(path, cmd->cmds, envp) == -1)
	{
		free(path);
		ft_error();
	}
}

void	child_process(t_pipexcmd *cmds, t_pipexcmd *current, int fd_prepipe,
		char **envp)
{
	setup_input(cmds, current, fd_prepipe);
	setup_output(cmds, current);
	execute_cmd(current, envp);
}

void	parent_process(t_pipexcmd *current, int *fd_prepipe)
{
<<<<<<< HEAD
	if (*fd_prepipe != -1)
		close(*fd_prepipe);
	if (current->nextnode)
	{
		close(current->tube[1]);
		*fd_prepipe = current->tube[0];
	}
=======
    (void)current;
    if (fd_prepipe != -1)
    {
        dup2(fd_prepipe, STDIN_FILENO);
        close(fd_prepipe);
    }
    else
    {
        dup2(cmds->infile, STDIN_FILENO);
        close(cmds->infile);
    }
>>>>>>> f813a4cc411a0fad719f3d100966b6a217cf04ec
}

void	process_commands(t_pipexcmd *cmds, t_pipexcmd *current, int *fd_prepipe,
		char **envp)
{
	while (current)
	{
		create_pipe(current);
		current->pid1 = fork();
		if (current->pid1 == -1)
			ft_error();
		if (current->pid1 == 0)
			child_process(cmds, current, *fd_prepipe, envp);
		else
			parent_process(current, fd_prepipe);
		current = current->nextnode;
	}
}

void	execute(t_pipexcmd *cmds, char **envp)
{
	t_pipexcmd	*current;
	int			fd_prepipe;

	current = cmds;
	fd_prepipe = -1;
	open_input_file(cmds);
	process_commands(cmds, current, &fd_prepipe, envp);
	wait_for_processes(cmds);
}
