/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matus <matus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 06:17:07 by matus             #+#    #+#             */
/*   Updated: 2024/11/14 06:19:02 by matus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft/libft.h"
#include "pipex.h"
#include "printf/ft_printf.h"

void	wait_child(t_pipex *pipex)
{
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	waitpid(pipex->pid1, NULL, 0);
	waitpid(pipex->pid2, NULL, 0);
}

void	parent_process(t_pipex *pipex)
{
	create_child1(pipex);
	create_child2(pipex);
	wait_child(pipex);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
	{
		return (EXIT_FAILURE);
	}
	init_structs(&pipex, envp, argv);
	parent_process(&pipex);
	ft_free_array(pipex.cmd1_args);
	ft_free_array(pipex.cmd2_args);
	return (EXIT_SUCCESS);
}
