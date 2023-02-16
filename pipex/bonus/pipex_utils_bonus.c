/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:24:26 by yuikim            #+#    #+#             */
/*   Updated: 2023/02/16 20:24:07 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	show_error(int exit_num, char *message1, char *message2)
{
	ft_putstr_fd("bash: ", 2);
	if (message1)
		ft_putstr_fd(message1, 2);
	if (message2)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(message2, 2);
	}
	ft_putstr_fd("\n", 2);
	exit(exit_num);
}

void	free_paths(t_arg *arg)
{
	int	i;

	i = 0;
	while (arg->paths[i])
	{
		free(arg->paths[i]);
		i++;
	}
	free(arg->paths);
}

void	delete_here_doc(t_arg *arg, char **envp)
{
	pid_t	pid;
	char	*cmd_path;
	char	**cmd_args;

	pid = fork();
	if (pid == -1)
		show_error(EXIT_FAILURE, "process failure", NULL);
	else if (pid == 0)
	{
		cmd_path = get_cmd_path("rm", arg->paths);
		cmd_args = ft_split("rm .here_doc_tmp", ' ');
		execve(cmd_path, cmd_args, envp);
	}
}
