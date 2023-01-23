#include "pipex_bonus.h"

int	control_first_connection(int idx, int pipes[2], char **argv, char **envp)
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

int	control_last_connection(int idx, int pipes[2], char **argv, char **envp)
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
	if (execve(cmd_path, outfile_arg, envp) == -1)
		show_error("no such file or directory");
	return (0);
}


int control_mid_connection(int idx, int pre_pipes[2], int next_pipes[2], char **argv, char **envp)
{
	char *s;
	char **paths;
	char **arguments;
	char *cmd_path;

	dup2(next_pipes[1], 1);
	dup2(pre_pipes[0], 0);
	close(next_pipes[0]);
	close(next_pipes[1]);
	close(pre_pipes[0]);
	close(pre_pipes[1]);
	s = get_path_env(envp);
	paths = ft_split(s, ':');
	arguments = parse(argv[idx]);
	cmd_path = find_path(arguments[0], paths);
	free(s);
	ft_free_dptr(paths);
	if (execve(cmd_path, arguments, envp) == -1)
		show_error("no such file or directory");
	return (0);
}

int control_mid_connection2(int idx, int pre_pipes[2], int next_pipes[2], t_setting *setting)
{
	char *s;
	char **paths;
	char **arguments;
	char *cmd_path;

	dup2(next_pipes[1], 1);
	dup2(pre_pipes[0], 0);
	close(next_pipes[0]);
	close(next_pipes[1]);
	close(pre_pipes[0]);
	close(pre_pipes[1]);
	s = get_path_env(setting->envp);
	paths = ft_split(s, ':');
	arguments = parse(setting->argv[idx]);
	cmd_path = find_path(arguments[0], paths);
	free(s);
	ft_free_dptr(paths);
	if (execve(cmd_path, arguments, setting->envp) == -1)
		show_error("no such file or directory");
	return (0);
}

int control_connection(int idx, int pre_pipes[2], char **argv, char **envp)
{
    int     next_pipes[2];
    pid_t   pid;

    if (pipe(next_pipes) == -1)
		show_error("pipe creation failure!");;
    pid = fork();
	if (pid == -1)
		show_error("child process creation failure!");
    else if (pid == 0 && idx - 1 == 2)
        control_first_connection(idx - 1, next_pipes, argv, envp);
	else if (pid == 0 && idx - 1 > 2)
		control_connection(idx - 1, next_pipes, argv, envp);
    else
        control_mid_connection(idx, next_pipes, pre_pipes, argv, envp);
	return (0);
}

int control_connection2(int idx, int pre_pipes[2], t_setting *setting)
{
    int     next_pipes[2];
    pid_t   pid;

    if (pipe(next_pipes) == -1)
		show_error("pipe creation failure!");;
    pid = fork();
	if (pid == -1)
		show_error("child process creation failure!");
    else if (pid == 0 && idx - 1 == 2)
        control_first_connection(idx - 1, next_pipes, setting->argv, setting->envp);
	else if (pid == 0 && idx - 1 > 2)
		control_connection2(idx - 1, next_pipes, setting);
    else
        control_mid_connection2(idx, next_pipes, pre_pipes, setting);
	return (0);
}

int main(int argc, char *argv[], char *envp[])
{
	int pipe2[2];

	pid_t	pid;
	t_setting *setting;

	setting = malloc(sizeof(t_setting));
	setting->argv = argv;
	setting->envp = envp;

	if (argc < 5)
		show_error("invalid input!");
	if (pipe(pipe2) == -1)
		show_error("pipe creation failure!");
	pid = fork();
	if (pid == -1)
		show_error("child process creation failure!");
	else if (pid == 0)
		// control_connection(get_height(argv) - 3, pipe2, argv, envp);
		control_connection2(get_height(argv) - 3, pipe2, setting);
	else
		control_last_connection(get_height(argv) -2, pipe2, argv, envp);
}