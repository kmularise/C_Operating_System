# ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "../libft/libft.h"
typedef struct	s_arg {
	int is_here_doc;
	int cmd_count;
	int infile_fd;
	int outfile_fd;
	int *pipes;
	int child_idx;
	int pipe_count;
	char **paths;
	pid_t *pids;
	char **cmd_args;
	char *cmd_path;
}	t_arg;

void free_paths(t_arg *arg);
void set_arg(t_arg *arg, int argc, char **argv, char **envps);
void create_pipes(t_arg *arg);
void close_pipes(t_arg *arg);
void    cmd_related_free(t_arg *arg, int option);
void child_dup2(int read_fd, int write_fd);
void close_pipes(t_arg *arg);
void	execute_child(t_arg arg, char **argv, char **envps);
void    cmd_related_free(t_arg *arg, int option);
void child_dup2(int read_fd, int write_fd);
void close_pipes(t_arg *arg);
void show_error(int exit_num, char *message1, char *message2);
char	**get_paths(char **envps);
char	*get_cmd_path(char *cmd, char **paths);
# define NO_CMD_PATH 0
# define CMD_PATH 1

#endif