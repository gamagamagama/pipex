/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matus <matus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:59:00 by matus             #+#    #+#             */
/*   Updated: 2024/11/14 06:20:29 by matus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include "printf/ft_printf.h"

void	child_process_cmd2(t_pipex *pipex)
{
	int	fd2;

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
	execve(pipex->path, pipex->cmd2_args, pipex->envp);
	perror("Failed to execute command write");
	exit(EXIT_FAILURE);
}

void	child_process_cmd1(t_pipex *pipex)
{
	int	fd1;

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
	execve(pipex->path, pipex->cmd1_args, pipex->envp);
	perror("Failed to execute command read");
	exit(EXIT_FAILURE);
}

void	create_child2(t_pipex *pipex)
{
	pid_t	pid2;

	if (create_pipes(pipex) == -1)
		exit(EXIT_FAILURE);
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
	pipex->pid2 = pid2;
}

void	create_child1(t_pipex *pipex)
{
	pid_t	pid1;

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
	pipex->pid1 = pid1;
}
