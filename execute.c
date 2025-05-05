/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorcher <mcorcher@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:31:16 by mcorcher          #+#    #+#             */
/*   Updated: 2025/05/05 20:31:19 by mcorcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void open_input_file(t_pipexcmd *cmds)
{
    cmds->infile = open(cmds->cmds[0], O_RDONLY);
    if (cmds->infile == -1)
        ft_error();
}

void create_pipe(t_pipexcmd *current)
{
    if (current->nextnode)
    {
        if (pipe(current->tube) == -1)
            ft_error();
    }
}

void setup_input(t_pipexcmd *cmds, t_pipexcmd *current, int fd_prepipe)
{
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

void setup_output(t_pipexcmd *cmds, t_pipexcmd *current)
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

void execute_cmd(t_pipexcmd *cmd, char **envp)
{
    char *path;

    path = find_path(cmd->cmds[0], envp);
    if(!path)
    {
        ft_printf("Command not found: %s\n", cmd->cmds[0]);
        exit(127);  // Error code in bassh used when the cmd is not found
    }
    
    if (execve(path, cmd->cmds, envp) == -1)
    {
        free(path);
        ft_error();
    }
}

void child_process(t_pipexcmd *cmds, t_pipexcmd *current, int fd_prepipe, char **envp)
{
    setup_input(cmds, current, fd_prepipe);
    setup_output(cmds, current);
    execute_cmd(current, envp);
}

void parent_process(t_pipexcmd *current, int *fd_prepipe)
{
    if (*fd_prepipe != -1)
        close(*fd_prepipe);
        
    if (current->nextnode)
    {
        close(current->tube[1]);
        *fd_prepipe = current->tube[0];
    }
}

void process_commands(t_pipexcmd *cmds, t_pipexcmd *current, int *fd_prepipe, char **envp)
{
    while (current)
    {
        create_pipe(current);
        
        // Create child process and check for errors
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

void wait_for_processes(t_pipexcmd *cmds)
{
    t_pipexcmd *current = cmds;
    
    while (current)
    {
        if (current->pid1 > 0)
            waitpid(current->pid1, &current->status, 0);
        current = current->nextnode;
    }
}

void execute(t_pipexcmd *cmds, char **envp)
{
    t_pipexcmd *current;
    int fd_prepipe;

    current = cmds;
    fd_prepipe = -1; // there is no previous pipe atm
    
    // With this call to the function we open our imput file (it uses our cmds + args)
    open_input_file(cmds);
    
    // We create our process and assign / parse PID
    process_commands(cmds, current, &fd_prepipe, envp);
    
    // We wait for our processes to end
    wait_for_processes(cmds);
}
