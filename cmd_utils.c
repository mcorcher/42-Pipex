/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorcher <mcorcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:48:52 by mcorcher          #+#    #+#             */
/*   Updated: 2025/05/18 19:06:09 by mcorcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// ------------------ MAIN PARSER FUNCTION ------------------
t_pipexcmd	*parsear_entrada(int argc, char **argv)
{
	t_pipexcmd	*head;

	head = init_head_node(argv[1], argv[argc - 1]);
	if (!head)
		return (NULL);
	if (!add_command_nodes(head, argc, argv))
	{
		free_cmd_list(head);
		return (NULL);
	}
	return (head);
}

// ------------------ WRAPPER ------------------
t_pipexcmd	*parsing_arg(int argc, char **argv)
{
	return (parsear_entrada(argc, argv));
}
