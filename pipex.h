/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matus <matus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 22:02:25 by matus             #+#    #+#             */
/*   Updated: 2024/11/14 06:27:17 by matus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include "printf/ft_printf.h"
# include "libft/libft.h"

typedef struct s_pipex
{
	char	*file1;
	char	*file2;
	char	**cmd1_args;
	char	**cmd2_args;
	char	**envp;
	char	*path_env;
	char	*path;
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
}	t_pipex;

void	init_structs(t_pipex *pipex, char **envp, char **argv);
void	parent_process(t_pipex *pipex);
void	child_process_cmd1(t_pipex *pipex);
void	child_process_cmd2(t_pipex *pipex);
void	ft_free_array(char **array);
void	get_path(t_pipex *pipex, char **cmd_args);
void	get_cmd_path(t_pipex *pipex, char **cmd_args, char **path_dir);
int		create_pipes(t_pipex *pipex);
void	create_child2(t_pipex *pipex);
void	wait_child(t_pipex *pipex);
void	create_child1(t_pipex *pipex);

int		main(int argc, char **argv, char **envp);

#endif