#include "pipex_bonus.h"

char *get_path(char **envp, char **argv, int idx)
{
	char *s;
	char **paths;
	char *cmd_path;

	s = get_path_env(envp);
	paths = ft_split(s, ':');
	cmd_path = find_path(argv[idx], paths);	
	free(s);
	ft_free_dptr(paths);
	return (cmd_path);
}

int control_communication2(int idx, int pre_pipes[2], char **argv, char **envp)//outfile 부분
{
	int fd_list[2];
	int next_pipe[2];
	char *cmd_path;
	char **arguments;

	if (idx == get_height(argv) - 2)
		fd_list[1] = open(argv[idx + 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	fd_list[0] = pre_pipes[0];
	dup2(fd_list[1], 1);
	dup2(fd_list[0], 0);
	close(fd_list[0]);
	close(pre_pipes[1]);
	close(fd_list[1]);

	arguments = parse(argv[idx]);
	cmd_path = get_path(envp, argv, idx);
	if (execve(cmd_path, arguments, envp) == -1)
		show_error("no such file or directory");
	return (0);
}

int control_communication3(int idx, int pre_pipes[2], int next_pipes[2], char **argv, char **envp)//중간 부분
{
	int fd_list[2];
	char *cmd_path;
	char **arguments;
	
	if (idx == 2)
		fd_list[0] = open(argv[1], O_RDONLY);
	else
		fd_list[0] = pre_pipes[0];
	fd_list[1] = next_pipes[1];
	dup2(fd_list[1], 1);
	dup2(fd_list[0], 0);
	close(pre_pipes[1]);
	close(next_pipes[0]);
	close(fd_list[1]);
	close(fd_list[0]);

	arguments = parse(argv[idx]);
	cmd_path = get_path(envp, argv, idx);
	if (execve(cmd_path, arguments, envp) == -1)
		show_error("no such file or directory");
	return (0);	
}

int control_communication4(int idx, int next_pipes[2], char **argv, char **envp)
{
	int fd_list[2];
	char *cmd_path;
	char **arguments;
	
	if (idx == 2)
		fd_list[0] = open(argv[1], O_RDONLY);
	// else
	// 	fd_list[0] = pre_pipes[0];
	fd_list[1] = next_pipes[1];
	dup2(fd_list[1], 1);
	dup2(fd_list[0], 0);
	// close(pre_pipes[1]);
	close(next_pipes[0]);
	close(fd_list[1]);
	close(fd_list[0]);

	arguments = parse(argv[idx]);
	cmd_path = get_path(envp, argv, idx);
	if (execve(cmd_path, arguments, envp) == -1)
		show_error("no such file or directory");
	return (0);	
}

int control_communication(int idx, int pre_pipes[2], char **argv, char **envp)
{
	int fd_list[2];
	int next_pipes[2];
	char *cmd_path;
	char **arguments;
	pid_t	pid;

	if (pipe(next_pipes)== -1)
		show_error("pipe creation failure!");
	pid = fork();
	if (pid == -1)
		show_error("child process creation failure!");
	else if (pid == 0)
	{
		if (idx - 1 == 2)
			control_communication4(idx, next_pipes, argv, envp);
	}
	else
	{
		control_communication3(idx, pre_pipes, next_pipes, argv, envp);
	}
	return (0);

}

int main(int argc, char *argv[], char *envp[])
{
	int		pipes[2];
	pid_t	pid;

	if (argc < 5)
		show_error("invalid input!");
	if (pipe(pipes) == -1)
		show_error("pipe creation failure!");
	pid = fork();
	if (pid == -1)
		show_error("child procss creation failure!");
	else if (pid == 0)
	{
		control_communication(get_height(argv) - 3, pipes, argv, envp);
	}
	else
	{
		control_communication2(get_height(argv) - 2, pipes, argv, envp);
	}

}