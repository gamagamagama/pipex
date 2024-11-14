/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matus <matus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 05:54:11 by matus             #+#    #+#             */
/*   Updated: 2024/11/14 06:27:13 by matus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	create_pipes(t_pipex *pipex)
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
	return (0);
}

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
}

void	get_cmd_path(t_pipex *pipex, char **cmd_args, char **path_dir)
{
	char	**tmp;

	tmp = path_dir;
	while (*tmp)
	{
		pipex->path = ft_strjoin(*tmp, "/");
		if (pipex->path)
		{
			pipex->path = ft_strjoin(pipex->path, cmd_args[0]);
			if (pipex->path)
			{
				if (access(pipex->path, X_OK) == 0)
					break ;
			}
			free(pipex->path);
			pipex->path = NULL;
		}
		tmp++;
	}
	if (!pipex->path)
	{
		exit(EXIT_FAILURE);
	}
}

void	get_path(t_pipex *pipex, char **cmd_args)
{
	char	**path_dir;

	if (!pipex->path_env)
	{
		while (*pipex->envp)
		{
			if (ft_strncmp(*pipex->envp, "PATH=", 5) == 0)
			{
				pipex->path_env = *pipex->envp + 5;
				break ;
			}
			pipex->envp++;
		}
	}
	if (!pipex->path_env)
	{
		exit(EXIT_FAILURE);
	}
	path_dir = ft_split(pipex->path_env, ':');
	if (!path_dir)
	{
		exit(EXIT_FAILURE);
	}
	get_cmd_path(pipex, cmd_args, path_dir);
	ft_free_array(path_dir);
}
