#include "pipex_bonus.h"
int	open_file_and_control_cmd2(int idx, int pipes[2], char **argv, char **envp)
{
	char	**infile_arg;
	char	*cmd_path;
	char	*s;
	int		fd0;
	char	**paths;
	fd0 = open(argv[idx - 1], O_RDONLY);
	dup2(fd0, 0);
	dup2(pipes[1], 1);
	close(pipes[0]);
	close(pipes[1]);
	close(fd0);
	s = get_path_env(envp);
	paths = ft_split(s, ':');
	infile_arg = parse(argv[idx]);
	cmd_path = find_path(infile_arg[0], paths);
	free(s);
	ft_free_dptr(paths);
	if (execve(cmd_path, infile_arg, envp) == -1)
		show_error("no such file or directory");
	return (0);
}

int	control_cmd_and_write_file2(int pipes[2], char **argv, char **envp)
{
	int		fd1;
	char	*s;
	char	**paths;
	char	**outfile_arg;
	char	*cmd_path;
	fd1 = open(argv[get_height(argv) - 1],
			O_RDWR | O_CREAT | O_TRUNC, 0777);
	dup2(fd1, 1);
	dup2(pipes[0], 0);
	close(pipes[0]);
	close(pipes[1]);
	close(fd1);
	s = get_path_env(envp);
	paths = ft_split(s, ':');
	outfile_arg = parse(argv[get_height(argv) - 2]);
	cmd_path = find_path(outfile_arg[0], paths);
	free(s);
	ft_free_dptr(paths);
	if (execve(cmd_path, outfile_arg, envp) == -1)
		show_error("no such file or directory");
	return (0);
}

int	control_cmd_and_write_file4(int idx, int pipes[2], char **argv, char **envp)
{
	int		fd1;
	char	*s;
	char	**paths;
	char	**outfile_arg;
	char	*cmd_path;
	fd1 = open(argv[idx + 1],
			O_RDWR | O_CREAT | O_TRUNC, 0777);
	dup2(fd1, 1);
	dup2(pipes[0], 0);
	close(pipes[0]);
	close(pipes[1]);
	close(fd1);
	s = get_path_env(envp);
	paths = ft_split(s, ':');
	outfile_arg = parse(argv[idx]);
	cmd_path = find_path(outfile_arg[0], paths);
	free(s);
	ft_free_dptr(paths);
	//printf("fdljfklajklsdj");
	if (execve(cmd_path, outfile_arg, envp) == -1)
		show_error("no such file or directory");
	return (0);
}


int control_mid_connection(int idx, int pre_pipes[2], int next_pipes[2], char **argv, char **envp)
{
	dup2(next_pipes[1], 1);
	dup2(pre_pipes[0], 0);
	close(next_pipes[0]);
	close(next_pipes[1]);
	close(pre_pipes[0]);
	close(pre_pipes[1]);
	char *s = get_path_env(envp);
	char **paths = ft_split(s, ':');
	char **infile_arg = parse(argv[idx]);
	char *cmd_path = find_path(infile_arg[0], paths);
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
	pid_t	pid2;
	if (argc != 6)
		show_error("invalid input!");
	if (pipe(pipe2) == -1)
		show_error("pipe creation failure!");
	pid = fork();
	if (pid == -1)
		show_error("child process creation failure!");
	else if (pid == 0)
	{
		pipe(pipe1);
		pid2 = fork();
		if(pid2 == 0)
			open_file_and_control_cmd2(2, pipe1, argv, envp);
		else
		{
			control_mid_connection(3, pipe1, pipe2, argv, envp);
		}
	}
	else
		control_cmd_and_write_file4(get_height(argv) -2, pipe2, argv, envp);
}