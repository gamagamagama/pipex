/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matus <matus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 22:02:25 by matus             #+#    #+#             */
/*   Updated: 2024/11/14 04:57:53 by matus            ###   ########.fr       */
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
}t_pipex;

void	init_structs(t_pipex *pipex, char **envp, char **argv);
void	parent_process(t_pipex *pipex);
void	child_process_cmd1(t_pipex *pipex);
void	child_process_cmd2(t_pipex *pipex);
void	ft_free_array(char **array);
void	get_path(t_pipex *pipex, char **cmd_args);
void	get_cmd_path(t_pipex *pipex, char **cmd_args, char **path_dir);
int	create_pipes(t_pipex *pipex);
// //debug
// void	print_cmd_args(char **cmd_args, const char *cmd_name);
// void	print_debug(const char *format, ...);

#endif