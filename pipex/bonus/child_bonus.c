/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:22:54 by yuikim            #+#    #+#             */
/*   Updated: 2023/02/17 21:24:23 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	child_dup2(int read_fd, int write_fd)
{
	dup2(read_fd, 0);
	dup2(write_fd, 1);
}

void	close_pipes(t_arg *arg)
{
	int	i;

	i = 0;
	while (i < arg->pipe_count)
	{
		close(arg->pipes[i]);
		i++;
	}
	close(arg->infile_fd);
	close(arg->outfile_fd);
}

void	execute_child(t_arg arg, char **argv, char **envps)
{
	if (arg.pids[arg.child_idx] == -1)
		show_error(EXIT_FAILURE, "process fork failure", NULL);
	else if (arg.pids[arg.child_idx] == 0)
	{
		if (arg.child_idx == 0)
			child_dup2(get_infile_fd(&arg, argv), arg.pipes[1]);
		else if (arg.child_idx == arg.cmd_count -1)
			child_dup2(arg.pipes[2 * arg.child_idx -2],
				get_outfile_fd(&arg, argv));
		else
			child_dup2(arg.pipes[2 * arg.child_idx - 2],
				arg.pipes[2 * arg.child_idx + 1]);
		close_pipes(&arg);
		arg.cmd_args = ft_split(argv[2 + arg.child_idx + arg.is_here_doc], ' ');
		arg.cmd_path = get_cmd_path(arg.cmd_args[0], arg.paths);
		if (!arg.cmd_path)
		{
			cmd_related_free(&arg, NO_CMD_PATH);
			show_error(EXIT_FAILURE,
				argv[2 + arg.is_here_doc + arg.child_idx], "command not found");
		}
		execve(arg.cmd_path, arg.cmd_args, envps);
	}
}
