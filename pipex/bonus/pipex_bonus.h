/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:09:48 by yuikim            #+#    #+#             */
/*   Updated: 2023/02/17 21:26:18 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>

# include "../libft/libft.h"

typedef struct s_arg {
	int		is_here_doc;
	int		cmd_count;
	int		infile_fd;
	int		outfile_fd;
	int		*pipes;
	int		child_idx;
	int		pipe_count;
	char	**paths;
	pid_t	*pids;
	char	**cmd_args;
	char	*cmd_path;
}	t_arg;

void	free_paths(t_arg *arg);
void	set_arg(t_arg *arg, int argc, char **argv, char **envps);
void	create_pipes(t_arg *arg);
void	child_dup2(int read_fd, int write_fd);
void	close_pipes(t_arg *arg);
void	execute_child(t_arg arg, char **argv, char **envps);
void	cmd_related_free(t_arg *arg, int option);
void	child_dup2(int read_fd, int write_fd);
void	show_error(int exit_num, char *message1, char *message2);
char	**get_paths(char **envps);
char	*get_cmd_path(char *cmd, char **paths);
void	set_here_doc(t_arg *arg, int argc, char **argv);
int		is_parent_process(t_arg arg);
void	delete_here_doc(t_arg *arg, char **envp);
int		get_infile_fd(t_arg *arg, char **argv);
int		get_outfile_fd(t_arg *arg, char **argv);

# define NO_CMD_PATH 0
# define CMD_PATH 1

#endif