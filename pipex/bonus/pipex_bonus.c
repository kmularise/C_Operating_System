/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:14:20 by yuikim            #+#    #+#             */
/*   Updated: 2023/02/17 21:17:08 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	set_here_doc(t_arg *arg, int argc, char **argv)
{
	int		temp_file_fd;
	char	*line;

	if (argc != 6)
		show_error(EXIT_FAILURE, "here_doc invalid input!", NULL);
	arg->is_here_doc = 1;
	temp_file_fd = open(".here_doc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line || (ft_strncmp(line, argv[2], ft_strlen(line) - 1) == 0
				&& ft_strlen(line) == ft_strlen(argv[2]) + 1))
			break ;
		if (!line)
			exit(EXIT_FAILURE);
		write(temp_file_fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(temp_file_fd);
}

void	set_arg(t_arg *arg, int argc, char **argv, char **envps)
{
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
		set_here_doc(arg, argc, argv);
	else
	{
		if (argc < 5)
			show_error(EXIT_FAILURE, "invalid input count!", NULL);
		arg->is_here_doc = 0;
	}
	arg->paths = get_paths(envps);
	arg->cmd_count = argc - 3 - arg->is_here_doc;
}

void	create_pipes(t_arg *arg)
{
	int	i;

	i = 0;
	while (i < arg->pipe_count)
	{
		if (pipe(&(arg->pipes)[2 * i]) < 0)
			show_error(EXIT_FAILURE, "pipe production failure", NULL);
		i++;
	}
}

int	is_parent_process(t_arg arg)
{
	int	i;

	i = -1;
	while (++i < arg.cmd_count)
	{
		if (arg.pids[i] == 0)
			return (0);
	}
	return (1);
}

int	main(int argc, char **argv, char **envps)
{
	t_arg	arg;
	int		i;

	set_arg(&arg, argc, argv, envps);
	arg.pipe_count = 2 * (arg.cmd_count - 1);
	arg.pipes = malloc(sizeof(int) * arg.pipe_count);
	create_pipes(&arg);
	arg.pids = malloc(sizeof(pid_t) * arg.cmd_count);
	arg.child_idx = -1;
	while (++(arg.child_idx) < arg.cmd_count)
	{
		arg.pids[arg.child_idx] = fork();
		execute_child(arg, argv, envps);
	}
	if (is_parent_process(arg))
	{
		close_pipes(&arg);
		i = -1;
		while (++i < arg.cmd_count)
			waitpid(arg.pids[i], NULL, 0);
		if (arg.is_here_doc)
			unlink(".here_doc_tmp");
		free_paths(&arg);
	}
	return (0);
}
