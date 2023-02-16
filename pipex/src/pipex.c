/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:42:17 by yuikim            #+#    #+#             */
/*   Updated: 2023/02/16 20:30:18 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	close_pipes(t_arg *arg)
{
	close(arg->pipes[0]);
	close(arg->pipes[1]);
	close(arg->infile_fd);
	close(arg->outfile_fd);
}

void	show_error(int exit_num, char *message1, char *message2)
{
	ft_putstr_fd("zsh: ", 2);
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

void	set_arg(t_arg *arg, int argc, char **argv, char **envps)
{
	if (argc != 5)
		show_error(EXIT_FAILURE, "argc is invalid", NULL);
	arg->infile_fd = open(argv[1], O_RDONLY);
	if (arg->infile_fd < 0)
		show_error(EXIT_FAILURE, "no such file or directory", argv[1]);
	arg->outfile_fd = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 000644);
	if (arg->outfile_fd < 0)
		show_error(EXIT_FAILURE, "no such file or directory", argv[argc - 1]);
	if (pipe(arg->pipes) < 0)
		show_error(EXIT_FAILURE, "pipe production failure", NULL);
	arg->paths = get_paths(envps);
	arg->cmd_count = 2;
}

int	main(int argc, char **argv, char **envps)
{
	t_arg	arg;
	int		idx;

	set_arg(&arg, argc, argv, envps);
	idx = -1;
	while (++idx < arg.cmd_count)
	{
		arg.pid[idx] = fork();
		if (arg.pid[idx] == -1)
			show_error(EXIT_FAILURE, "process fork failure", NULL);
		else if (idx == 0 && arg.pid[idx] == 0)
			execute_first_child(arg, argv, envps);
		else if (idx == 1 && arg.pid[idx] == 0)
			execute_second_child(arg, argv, envps);
	}
	if (arg.pid[0] != 0 && arg.pid[1] != 0)
	{
		close_pipes(&arg);
		waitpid(arg.pid[0], NULL, 0);
		waitpid(arg.pid[1], NULL, 0);
		free_paths(&arg);
	}
}
