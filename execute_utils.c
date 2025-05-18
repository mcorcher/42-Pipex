/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorcher <mcorcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:51:12 by mcorcher          #+#    #+#             */
/*   Updated: 2025/05/18 18:52:38 by mcorcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_input_file(t_pipexcmd *cmds)
{
	cmds->infile = open(cmds->cmds[0], O_RDONLY);
	if (cmds->infile == -1)
		ft_error();
}

void	create_pipe(t_pipexcmd *current)
{
	if (current->nextnode)
	{
		if (pipe(current->tube) == -1)
			ft_error();
	}
}

void	setup_input(t_pipexcmd *cmds, t_pipexcmd *current, int fd_prepipe)
{
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
}

void	setup_output(t_pipexcmd *cmds, t_pipexcmd *current)
{
	if (current->nextnode)
	{
		close(current->tube[0]);
		dup2(current->tube[1], STDOUT_FILENO);
		close(current->tube[1]);
	}
	else
	{
		cmds->outfile = open(cmds->cmds[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmds->outfile == -1)
			ft_error();
		dup2(cmds->outfile, STDOUT_FILENO);
		close(cmds->outfile);
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
