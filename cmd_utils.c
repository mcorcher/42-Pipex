/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorcher <mcorcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 05:42:16 by mcorcher          #+#    #+#             */
/*   Updated: 2025/05/19 05:42:34 by mcorcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipexcmd	*parsear_entrada(int argc, char **argv)
{
	t_pipexcmd	*head;

	head = initialize_head(argc, argv);
	if (!head)
		return (NULL);
	head = add_commands_to_list(argc, argv, head);
	return (head);
}

t_pipexcmd	*parsing_arg(int argc, char **argv)
{
	return (parsear_entrada(argc, argv));
}
