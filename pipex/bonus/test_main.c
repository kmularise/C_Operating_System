/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 16:44:06 by yuikim            #+#    #+#             */
/*   Updated: 2023/01/07 20:44:48 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	open_file_and_control_cmd(int pipes[2], char **argv, char **envp)
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

int	connect_pipe(int pipes[2], int pre_pipes[2], char *cmd, char **envp)//write
{
	char	**cmd_arg;
	char	*cmd_path;
	char	*s;
	char	**paths;

	dup2(pre_pipes[0], 0);
	dup2(pipes[1], 1);
	close(pipes[0]);
	close(pre_pipes[1]);
	//close(pre_pipes[0]);
	//close(pipes[1]);
	//close(pre_pipes[1]); //close pre_pipes를 또 다시 해야 하나 pipe는 부모 쪽에서 만드나.
	s = get_path_env(envp);
	paths = ft_split(s, ':');
	cmd_arg = parse(cmd);
	cmd_path = find_path(cmd_arg[0], paths);
	free(s);
	ft_free_dptr(paths);
	if (execve(cmd_path, cmd_arg, envp) == -1)
		show_error("no such file or directory");
	return (0);
}

int	connect_pipe2(int pipes[2], int pre_pipes[2], char *cmd, char **envp)//write
{
	char	**cmd_arg;
	char	*cmd_path;
	char	*s;
	char	**paths;
	//printf("%s\n", cmd);
	dup2(pre_pipes[0], 0);
	//dup2(pipes[1], 1);
	close(pipes[0]);
	close(pre_pipes[1]);
	// close(pre_pipes[0]);
	// close(pipes[1]);
	//close(pre_pipes[1]); //close pre_pipes를 또 다시 해야 하나 pipe는 부모 쪽에서 만드나.
	s = get_path_env(envp);
	paths = ft_split(s, ':');
	cmd_arg = parse(cmd);
	cmd_path = find_path(cmd_arg[0], paths);
	free(s);
	ft_free_dptr(paths);
	if (execve(cmd_path, cmd_arg, envp) == -1)
		show_error("no such file or directory");
	return (0);
}

int	control_cmd_and_write_file(int pipes[2], char **argv, char **envp)
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

int	control_pipe_and_cmd(int pre_pipes[2], int cmd_count,
	char **argv, char **envp)
{
	int		pipes[2];
	pid_t	pid;
	if (cmd_count == get_height(argv) - 3)
	{
		control_cmd_and_write_file(pre_pipes, argv, envp);
		return (0);
	}
	if (pipe(pipes) == -1)
		show_error("pipe creation failure!");
	pid = fork();
	if (pid == -1)
		show_error("child process creation failure!");
	else if (pid != 0)
	{
		if (cmd_count == 2)
			connect_pipe2(pipes, pre_pipes, argv[cmd_count + 1], envp);
		else
			connect_pipe(pipes, pre_pipes, argv[cmd_count + 1], envp);
	}
	else
	{
		//printf("mother\n");
		control_pipe_and_cmd(pipes, cmd_count + 1, argv, envp);
		// if (cmd_count == 3)
		// 	control_pipe_and_cmd2(pipes, cmd_count + 1, argv, envp);			

		//get_pipe(pipes, pre_pipes, argv[cmd_count], envp);
		// control_pipe_and_cmd(pipes, cmd_count + 1, argv, envp);
	}
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		pipes[2];
	pid_t	pid;

	if (argc < 5)
		show_error("invalid input!");
	if (pipe(pipes) == -1)
		show_error("pipe creation failure!");
	pid = fork();
	if (pid == -1)
		show_error("child process creation failure!");
	else if (pid != 0)
		open_file_and_control_cmd(pipes, argv, envp);
	else
		control_pipe_and_cmd(pipes, 2, argv, envp);
}
