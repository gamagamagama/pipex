/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matus <matus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:59:00 by matus             #+#    #+#             */
/*   Updated: 2024/11/14 05:43:43 by matus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include "printf/ft_printf.h"

void	ft_free_array(char **array)
{
    int i = 0;
    while (array[i] != NULL)
    {
        free(array[i]);
        i++;
    }
    free(array);
}

// Print to stderr for debugging
// void print_debug(const char *format, ...)
// {
//     va_list args;
//     va_start(args, format);
//     vfprintf(stderr, format, args);
//     va_end(args);
// }

// void	print_cmd_args(char **cmd_args, const char *cmd_name)
// {
// 	int i = 0;
// 	//print_debug("Arguments for %s:\n", cmd_name);
// 	while (cmd_args[i])
// 	{
// 		//print_debug("  %s\n", cmd_args[i]);
// 		i++;
// 	}
// }

void	init_structs(t_pipex *pipex, char **envp, char **argv)
{
	pipex->file1 = argv[1];
	pipex->cmd1_args = ft_split(argv[2], ' ');
	pipex->cmd2_args = ft_split(argv[3], ' ');
	pipex->file2 = argv[4];
	pipex->envp = envp;
	pipex->path_env = NULL;
	pipex->path = NULL;
	pipex->pipe_fd[0] = -1;
	pipex->pipe_fd[1] = -1;
	// Debug output
	//print_debug("Initialized structures with file1: %s, file2: %s\n", pipex->file1, pipex->file2);
	// print_cmd_args(pipex->cmd1_args, "cmd1");
	// print_cmd_args(pipex->cmd2_args, "cmd2");
}

void get_cmd_path(t_pipex *pipex, char **cmd_args, char **path_dir)
{
    char **tmp = path_dir;
    while (*tmp)
    {
        pipex->path = ft_strjoin(*tmp, "/");
        if (pipex->path)
        {
            pipex->path = ft_strjoin(pipex->path, cmd_args[0]);
            if (pipex->path)
            {
                //print_debug("Trying path: %s\n", pipex->path);
                if (access(pipex->path, X_OK) == 0) 
                    break;
                //print_debug("Path is not executable: %s\n", pipex->path);
            }
            free(pipex->path);
            pipex->path = NULL;
        }
        tmp++;
    }
 	if (!pipex->path)
    {
        //print_debug("Command not found: %s\n", cmd_args[0]);
        exit(EXIT_FAILURE);
    }
    //print_debug("Command path found: %s\n", pipex->path);
}

void get_path(t_pipex *pipex, char **cmd_args)
{
    char **path_dir;
    //print_debug("Looking for PATH environment variable...\n");
	if (!pipex->path_env)
	{
		while (*pipex->envp)
    	{
        	if (ft_strncmp(*pipex->envp, "PATH=", 5) == 0)
        	{
            	pipex->path_env = *pipex->envp + 5;
            	break;
        	}
        	pipex->envp++;
    	}
	}
    if (!pipex->path_env)
    {
        //print_debug("PATH environment variable not found\n");
        exit(EXIT_FAILURE);
    }
    //print_debug("PATH found: %s\n", pipex->path_env);

    path_dir = ft_split(pipex->path_env, ':');
    if (!path_dir)
    {
        //print_debug("Failed to split PATH directories\n");
        exit(EXIT_FAILURE);
    }
    get_cmd_path(pipex, cmd_args, path_dir);
    //get_cmd_path(pipex, pipex->cmd2_args, path_dir);
    ft_free_array(path_dir);
	//ft_free_array(pipex->cmd1_args);
	//ft_free_array(pipex->cmd2_args);
}

int create_pipes(t_pipex *pipex)
{
	if (pipex->pipe_fd[0] != -1 && pipex->pipe_fd[1] != -1)
	{
		close(pipex->pipe_fd[0]);
		close(pipex->pipe_fd[1]);
	}
	if (pipe(pipex->pipe_fd) == -1)
	{
		perror("Pipe creation failed");
		return (-1);
	}
	//print_debug("Pipe created with fds: %d, %d\n", pipex->pipe_fd[0], pipex->pipe_fd[1]);
	return (0);
}

void child_process_cmd2(t_pipex *pipex)
{
	int fd2;
	//print_debug("Opening file2 for cmd2: %s\n", pipex->file2);
	fd2 = open(pipex->file2, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd2 == -1)
	{
		perror("Failed to open output file fd2");
		exit(EXIT_FAILURE);
	}
	dup2(fd2, STDOUT_FILENO);
	close(fd2);
	dup2(pipex->pipe_fd[0], STDIN_FILENO);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	get_path(pipex, pipex->cmd2_args);
	//debug
	//print_debug("Executing cmd2 with path: %s\n", pipex->path);
	// print_cmd_args(pipex->cmd2_args, "cmd2");
	//debug
	execve(pipex->path, pipex->cmd2_args, pipex->envp);
	perror("Failed to execute command write");
	exit(EXIT_FAILURE);
}

void child_process_cmd1(t_pipex *pipex)
{
	int fd1;
	//print_debug("Opening file1 for cmd1: %s\n", pipex->file1);
	fd1 = open(pipex->file1, O_RDONLY);
	if (fd1 == -1)
	{
		perror("Failed to input file fd1");
		exit(EXIT_FAILURE);
	}
	dup2(fd1, STDIN_FILENO);
	close(fd1);
	dup2(pipex->pipe_fd[1], STDOUT_FILENO);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	get_path(pipex, pipex->cmd1_args);
	//debug
	//print_debug("Executing cmd1 with path: %s\n", pipex->path);
	// print_cmd_args(pipex->cmd1_args, "cmd1");
	//debug
	execve(pipex->path, pipex->cmd1_args, pipex->envp);
	perror("Failed to execute command read");
	exit(EXIT_FAILURE);
}

void parent_process(t_pipex *pipex)
{
	pid_t pid1;
	pid_t pid2;

	if (create_pipes(pipex) == -1)
		exit(EXIT_FAILURE);

	pid1 = fork();
	if (pid1 == -1)
	{
		perror("Failed to create first child process");
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0)
	{
		child_process_cmd1(pipex);
		exit(EXIT_SUCCESS);
	}

	pid2 = fork();
	if (pid2 == -1)
	{
		perror("Failed to create second child process");
		exit(EXIT_FAILURE);
	}
	if (pid2 == 0)
	{
		child_process_cmd2(pipex);
		exit(EXIT_SUCCESS);
	}

	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	//print_debug("Parent process: children completed.\n");
}

int main(int argc, char **argv, char **envp)
{
	t_pipex pipex;

	if (argc != 5)
	{
		//print_debug("Usage: ./pipex file1 cmd1 cmd2 file2\n");
		return (EXIT_FAILURE);
	}
	init_structs(&pipex, envp, argv);
	parent_process(&pipex);
	ft_free_array(pipex.cmd1_args);
	ft_free_array(pipex.cmd2_args);
	return (EXIT_SUCCESS);
}
