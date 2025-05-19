/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorcher <mcorcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 05:44:36 by mcorcher          #+#    #+#             */
/*   Updated: 2025/05/19 05:44:37 by mcorcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(t_pipexcmd *cmds, t_pipexcmd *current, int fd_prepipe,
		char **envp)
{
	setup_input(cmds, current, fd_prepipe);
	setup_output(cmds, current);
	execute_cmd(current, envp);
}

void	parent_process(t_pipexcmd *current, int *fd_prepipe)
{
	if (*fd_prepipe != -1)
		close(*fd_prepipe);
	if (current->nextnode)
	{
		close(current->tube[1]);
		*fd_prepipe = current->tube[0];
	}
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

void	wait_for_processes(t_pipexcmd *cmds)
{
	t_pipexcmd	*current;

	current = cmds;
	while (current)
	{
		if (current->pid1 > 0)
			waitpid(current->pid1, &current->status, 0);
		current = current->nextnode;
	}
}

void	execute(t_pipexcmd *cmds, char **envp)
{
	t_pipexcmd	*current;
	int			fd_prepipe;

	current = cmds->nextnode;
	fd_prepipe = -1;
	open_input_file(cmds);
	process_commands(cmds, current, &fd_prepipe, envp);
	wait_for_processes(cmds);
}
