/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:29:52 by yuikim            #+#    #+#             */
/*   Updated: 2023/02/16 20:29:54 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_paths(char **envps)
{
	int		i;
	char	**paths;

	i = 0;
	while (envps[i])
	{
		if (ft_strncmp(envps[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	paths = ft_split(&envps[i][5], ':');
	return (paths);
}

void	cmd_related_free(t_arg *arg, int option)
{
	int	i;

	i = 0;
	while (arg->cmd_args[i])
	{
		free(arg->cmd_args[i]);
		i++;
	}
	free(arg->cmd_args);
	if (option == CMD_PATH)
		free(arg->cmd_path);
}

char	*get_cmd_path(char *cmd, char **paths)
{
	int		i;
	char	*cmd_path;
	char	*temp;

	i = 0;
	cmd_path = NULL;
	if (!cmd)
		(NULL);
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], "/");
		temp = cmd_path;
		cmd_path = ft_strjoin(cmd_path, cmd);
		free(temp);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	if (access(cmd, F_OK) == 0)
		return (cmd);
	return (NULL);
}

void	execute_first_child(t_arg arg, char **argv, char **envp)
{
	dup2(arg.pipes[1], 1);
	close(arg.pipes[0]);
	dup2(arg.infile_fd, 0);
	arg.cmd_args = ft_split(argv[2], ' ');
	arg.cmd_path = get_cmd_path(arg.cmd_args[0], arg.paths);
	if (!arg.cmd_path)
	{
		cmd_related_free(&arg, NO_CMD_PATH);
		show_error(EXIT_FAILURE, argv[2], "command not found");
	}
	execve(arg.cmd_path, arg.cmd_args, envp);
}

void	execute_second_child(t_arg arg, char **argv, char **envp)
{
	dup2(arg.pipes[0], 0);
	close(arg.pipes[1]);
	dup2(arg.outfile_fd, 1);
	arg.cmd_args = ft_split(argv[3], ' ');
	arg.cmd_path = get_cmd_path(arg.cmd_args[0], arg.paths);
	if (!arg.cmd_path)
	{
		cmd_related_free(&arg, NO_CMD_PATH);
		show_error(EXIT_FAILURE, argv[3], "command not found");
	}
	execve(arg.cmd_path, arg.cmd_args, envp);
}
