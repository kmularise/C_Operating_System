#include "pipex_bonus.h"

int	open_file_and_control_cmd2(int pipes[2], char **argv, char **envp)
{
	char	**infile_arg;
	char	*cmd_path;
	char	*s;
	int		fd0;
	char	**paths;

	fd0 = open(argv[1], O_RDONLY);
	dup2(fd0, 0);//처음 start
	dup2(pipes[1], 1);//처음 start
	close(pipes[0]);//닫아줘야 함
	close(pipes[1]);//필요 없음
	close(fd0);//필요 없음
	s = get_path_env(envp);
	paths = ft_split(s, ':');
	infile_arg = parse(argv[2]);
	cmd_path = find_path(infile_arg[0], paths);
	free(s);
	ft_free_dptr(paths);
	if (execve(cmd_path, infile_arg, envp) == -1)
		show_error("no such file or directory");
	return (0);
}

int	open_file_and_control_cmd2(int pre_pipes[2], int next_pipes[2], char **argv, char **envp)
{
	char	**infile_arg;
	char	*cmd_path;
	char	*s;
	int		fd0;
	char	**paths;

	dup2()
	dup2(fd0, 0);//처음 start
	dup2(pipes[1], 1);//처음 start
	close(pipes[0]);//닫아줘야 함
	close(pipes[1]);//필요 없음
	close(fd0);//필요 없음
	s = get_path_env(envp);
	paths = ft_split(s, ':');
	infile_arg = parse(argv[2]);
	cmd_path = find_path(infile_arg[0], paths);
	free(s);
	ft_free_dptr(paths);
	if (execve(cmd_path, infile_arg, envp) == -1)
		show_error("no such file or directory");
	return (0);
}

int main(int argc, char *argv[], char *envp[])
{
	int pipe1[2];
	int pipe2[2];
	pid_t	pid;
	pid_t	pid2

	if (argc != 6)
		show_error("invalid input!");
	if (pipe(pipe1) == -1)
		show_error("pipe creation failure!");
	pid = fork();
	if (pid == -1)
		show_error("child process creation failure!");
	else if (pid == 0)
	{
		open_file_and_control_cmd2(pipe1, argv, envp);
	}
	else
	{
		if (pipe(pipe2) == -1)
			show_error("pipe creation failure!");
		pid2 = fork();
		if (pid2 == -1)
			show_error("child process creation failure!");
		else if (pid2== 0)
		{

		}
		else if(pid2 != )
		{

		}
	}

}