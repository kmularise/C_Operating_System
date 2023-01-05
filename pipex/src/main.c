/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:30:31 by yuikim            #+#    #+#             */
/*   Updated: 2023/01/05 09:19:41 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "parser.c"
#include "finder.c"
void	memory_leak(void)
{
	system("leaks a.out");
}

void	show_error(char *error_message)
{
	perror(error_message);
	exit(1);
}

int	do_infile_process(int pipes[2], char **argv, char **envp)
{
	char	**infile_arg;
	char	*cmd_path;
	char	*s;
	int		fd0;
	char	**paths;

	fd0 = open(argv[1], O_RDONLY);
	dup2(fd0, 0);
	dup2(pipes[1], 1);
	close(pipes[0]);
	close(pipes[1]);
	close(fd0);
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

int	do_outfile_process(int pipes[2], char **argv, char **envp)
{
	int		fd1;
	char	*s;
	char	**paths;
	char	**outfile_arg;
	char	*cmd_path;

	fd1 = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	dup2(fd1, 1);
	dup2(pipes[0], 0);
	close(pipes[0]);
	close(pipes[1]);
	close(fd1);
	s = get_path_env(envp);
	paths = ft_split(s, ':');
	outfile_arg = parse(argv[3]);
	cmd_path = find_path(outfile_arg[0], paths);
	free(s);
	ft_free_dptr(paths);
	if (execve(cmd_path, outfile_arg, envp) == -1)
		show_error("no such file or directory");
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		pipes[2];
	char	*backup;
	pid_t	pid;

	if (argc != 5)
		show_error("invalid input!");
	if (pipe(pipes) == -1)
		show_error("pipe creation failure!");
	pid = fork();
	if (pid == -1)
		show_error("child process creation failure!");
	else if (pid == 0)
		do_infile_process(pipes, argv, envp);
	else
		do_outfile_process(pipes, argv, envp);
	return (0);
}
