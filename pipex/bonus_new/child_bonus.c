#include "pipex_bonus.h"

void child_dup2(int read_fd, int write_fd)
{
	dup2(read_fd, 0);
	dup2(write_fd, 1);
}

void close_pipes(t_arg *arg)
{
	int	i;

	i = 0;
	while (i < arg->pipe_count)
	{
		close(arg->pipes[i]);
		i++;
	}
}

void	execute_child(t_arg arg, char **argv, char **envps)
{
	arg.pid = fork();
	if (arg.pid == 0)
	{
		if (arg.child_idx == 0)
			child_dup2(arg.infile_fd, arg.pipes[1]);
		else if (arg.child_idx == arg.cmd_count -1)
			child_dup2(arg.pipes[2 * arg.child_idx -2], arg.outfile_fd);
		else
			child_dup2(arg.pipes[2 * arg.child_idx - 2], arg.pipes[2 * arg.child_idx + 1]);
		close_pipes(&arg);
		arg.cmd_args = ft_split(argv[2 + arg.child_idx], ' ');
		arg.cmd_path = get_cmd_path(arg.cmd_args[0], arg.paths);
		if (!arg.cmd_path)
		{
			show_error(EXIT_FAILURE, argv[2 + arg.child_idx], "command not found");
		}

	}
}
