/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorcher <mcorcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 05:45:08 by mcorcher          #+#    #+#             */
/*   Updated: 2025/05/19 05:45:09 by mcorcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_input_file(t_pipexcmd *cmds)
{
	cmds->infile = open(cmds->infile_path, O_RDONLY);
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
		cmds->outfile = open(cmds->outfile_path, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (cmds->outfile == -1)
			ft_error();
		dup2(cmds->outfile, STDOUT_FILENO);
		close(cmds->outfile);
	}
}

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
