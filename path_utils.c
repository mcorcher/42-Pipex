/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorcher <mcorcher@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:31:50 by mcorcher          #+#    #+#             */
/*   Updated: 2025/05/05 20:31:52 by mcorcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_error(void)
{
    perror("\033[31mError");
    exit(EXIT_FAILURE);
}

char *get_path(char **envp)
{
    int i = 0;

    while (envp[i] && ft_strncmp("PATH=", envp[i], 5))
        i++;
    if (!envp[i])
        return (NULL);
    return (envp[i] + 5);     
}

void free_paths(char **paths)
{
    int i = 0;
    while (paths && paths[i])
        free(paths[i++]);
    free(paths);
}

char *build_valid_path(char **paths, char *cmd)
{
    int i = 0;
    char *part_path;
    char *full_path;

    while (paths[i])
    {
        part_path = ft_strjoin(paths[i], "/");
        if (!part_path)
            return (NULL);
        full_path = ft_strjoin(part_path, cmd);
        free(part_path);
        if (!full_path)
            return (NULL);
        if (access(full_path, F_OK | X_OK) == 0)
            return (full_path);
        free(full_path);
        i++;
    }
    return (NULL);
}

char *find_path(char *cmd, char **envp)
{
    char *env_path;
    char **paths;
    char *result;

    if (cmd[0] == '/' || (cmd[0] == '.' && (cmd[1] == '/' || cmd[1] == '.')))
    {
        if (access(cmd, F_OK | X_OK) == 0)
            return (ft_strdup(cmd));
        return (NULL);
    }
    env_path = get_path(envp);
    if (!env_path)
        return (NULL);
    paths = ft_split(env_path, ':');
    if (!paths)
        return (NULL);
    result = build_valid_path(paths, cmd);
    free_paths(paths);
    return (result);
}
