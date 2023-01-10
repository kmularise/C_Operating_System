#include "pipex_bonus.h"

char *get_cmd_path(char **envp, char **argv, int idx)
{
	char	*s;
	char	**paths;
	char	*cmd_path;

	s = get_path_env(envp);
	paths = ft_split(s, ':');
	cmd_path = find_path(argv[idx], paths);
	free(s);
	ft_free_dptr(paths);
	return (cmd_path);
}

int control_cmd_process(int idx, char **argv, char **envp, int pre_pipes[2], int next_pipes[2])
{
	char **arguments;
	char *cmd_path;
	int	temp[2];

	if (idx == 2)
		temp[0] = open(argv[1], O_RDONLY);
	else
	{
		temp[0] = pre_pipes[0];
		close(pre_pipes[1]);
	}
	if (idx == get_height(argv) - 2)
	{
		temp[1] = open(argv[get_height(argv) - 1],
			O_RDWR | O_CREAT | O_TRUNC, 0777);
	}
	else
	{
		temp[1] = next_pipes[1];
		close(next_pipes[0]);
	}
	dup2(temp[1], 1);
	dup2(temp[0], 0);

	cmd_path = get_cmd_path(envp, argv, idx);
	arguments = parse(argv[idx]);
	if (execve(cmd_path, arguments, envp) == -1)
		show_error("no such file or directory");
	exit(0);
}


void control_pipe(int idx, char **argv, char **envp, int pre_pipes[2])
{
	int		pipes[2];
	pid_t	pid;


	if (pipe(pipes) == -1)
		show_error("pipe creation failure!");
	if (idx != get_height(envp) - 2)
	{	
		pid = fork();
		if (pid == -1)
			show_error("child process creation failure!");
		else if (pid == 0)
			control_pipe(idx + 1, argv, envp, pipes);
	}
	else
		control_cmd_process(idx, argv, envp, pipes, pre_pipes);
}

int main (int argc, char **argv[], char *envp[])
{
	int init[2];
	if (argc < 5)
		show_error("invalid input!");
	init[0] = -2;
	init[1] = -1;
	control_pipe(2, argv, envp, init);
}