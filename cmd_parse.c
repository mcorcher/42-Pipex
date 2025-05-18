/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorcher <mcorcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:24:13 by mcorcher          #+#    #+#             */
/*   Updated: 2025/05/18 19:16:57 by mcorcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_cmd_list(t_pipexcmd *head)
{
	t_pipexcmd	*temp;
	int			j;

	while (head)
	{
		temp = head->nextnode;
		if (head->cmds)
		{
			j = 0;
			while (head->cmds[j])
				free(head->cmds[j++]);
			free(head->cmds);
		}
		free(head);
		head = temp;
	}
}

// ------------------ INITIALIZE HEAD ------------------
t_pipexcmd	*init_head_node(char *infile, char *outfile)
{
	t_pipexcmd	*head;

	head = parsing_arg_initialize();
	if (!head)
		return (NULL);
	head->cmds = malloc(sizeof(char *) * 2);
	if (!head->cmds)
	{
		free(head);
		return (NULL);
	}
	head->cmds[0] = ft_strdup(infile);
	head->cmds[1] = ft_strdup(outfile);
	return (head);
}

// ------------------ ADD COMMAND NODES ------------------
int	add_command_nodes(t_pipexcmd *head, int argc, char **argv)
{
	t_pipexcmd	*current;
	t_pipexcmd	*new_cmd;
	int			i;

	current = head;
	i = 2;
	while (i < argc - 1)
	{
		new_cmd = crea_comando(argv[i]);
		if (!new_cmd)
			return (0);
		current->nextnode = new_cmd;
		current = new_cmd;
		i++;
	}
	new_cmd = crea_comando(argv[i]);
	if (!new_cmd)
		return (0);
	current->nextnode = new_cmd;
	return (1);
}

// ------------------ CREATE SINGLE COMMAND NODE ------------------
t_pipexcmd	*crea_comando(char *cmd)
{
	t_pipexcmd	*new_cmd;
	int			i;

	i = 0;
	new_cmd = malloc(sizeof(t_pipexcmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->nextnode = NULL;
	new_cmd->cmds = ft_split(cmd, ' ');
	if (!new_cmd->cmds)
	{
		free(new_cmd);
		return (NULL);
	}
	while (new_cmd->cmds[i])
		i++;
	new_cmd->argc = i;
	new_cmd->status = 0;
	return (new_cmd);
}

// ------------------ INITIAL HEAD WRAPPER ------------------
t_pipexcmd	*parsing_arg_initialize(void)
{
	t_pipexcmd	*head;

	head = malloc(sizeof(t_pipexcmd));
	if (!head)
		return (NULL);
	head->nextnode = NULL;
	head->cmds = NULL;
	return (head);
}
