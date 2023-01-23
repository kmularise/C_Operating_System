#include "get_next_line.h"
#include "pipex_bonus.h"
#include <stdbool.h>
#include <stdio.h>

bool is_equal(char *str, char *target)
{
    int i;

    i = 0;
    while (target[i])
    {
        if (target[i] != str[i])
            return false;
        i++;
    }
    if (str[i])
        return false;
    return true;
}

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

char    *get_here_docs(char *target)
{
    char    *line;
    char *text;
    char *temp;

    text = malloc(sizeof(char));
    text[0] = 0;
    while (1)
    {
        line = get_next_line(0);
        if (is_equal(line, target))
        {
            free(line);
            break;
        }
        temp = text;
        text = ft_strjoin(text, line);
        free(temp);
        free(line);
    }
    return (text);
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

int control_heredoc_connection(char **argv, int pre_pipes[2], char *docs)
{
    close(pre_pipes[0]);
    write(pre_pipes[1], docs, ft_strlen(docs));
    return (0);
}

int control_mid_connection(int idx, int pre_pipes[2], int next_pipes[2], t_setting *setting)
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

int control_pre_connection(int pre_pipes[2], int next_pipes[2], char **argv, char **envp)
{
    char *buffer;
    int bytes;

    // buffer = malloc(sizeof(char) * 1000);
    close(pre_pipes[1]);
    // bytes = read(pre_pipes[0], buffer, 1000);
    // buffer[bytes] = 0;
    // write(1, buffer, ft_strlen(buffer));
    free(buffer);
    return (0);
}

int main(int argc, char **argv, char **envp)
{
    int     pre_pipes[2];
    int     next_pipes[2];
    char    *docs;
    char    *eof;
    pid_t   pid;
    pid_t   pid2;

    t_setting *setting;

	setting = malloc(sizeof(t_setting));
	setting->argv = argv;
	setting->envp = envp;

    // if (argc != 6)
    //     show_error("invalid input!");
    if (/*is_equal(argv[1], "here_doc")*/1)
    {
        eof = ft_strjoin(argv[2], "\n");
        docs = get_here_docs(eof);
        free(eof);

        if (pipe(next_pipes) == -1)
            show_error("pipe creation failure!");
        pid = fork();
	    if (pid == -1)
		    show_error("child process creation failure!");
        else if (pid == 0)
        {
            if (pipe(pre_pipes) == -1)
                show_error("pipe creation failure!");
            pid2 = fork();
            if (pid2 == -1)
                show_error("child process creation failure!");
            else if (pid2 == 0)
            {
                // control_first_connection(2, pre_pipes, argv, envp);
                 control_heredoc_connection(argv, pre_pipes, docs);
            }
            else
                control_mid_connection(3, pre_pipes, next_pipes, setting);
        }
        else
            control_last_connection(4, next_pipes, setting->argv, setting->envp);
    }
    // system("leaks a.out");
    return (0);
}