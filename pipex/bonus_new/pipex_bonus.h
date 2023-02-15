# ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "../libft/libft.h"
typedef struct	s_arg {
	int cmd_count;
	int infile_fd;
	int outfile_fd;
	int *pipes;
	int pipe_count;
	char **paths;
	pid_t pid[2];
	char **cmd_args;
	char *cmd_path;
}	t_arg;

void    cmd_related_free(t_arg *arg, int option);
void show_error(int exit_num, char *message1, char *message2);
char	**get_paths(char **envps);
char	*get_cmd_path(char *cmd, char **paths);
void execute_first_child(t_arg arg, char **argv, char **envp);
void execute_second_child(t_arg arg, char **argv, char **envp);
void set_arg(t_arg *arg, int argc, char **argv, char **envps);
# define NO_CMD_PATH 0
# define CMD_PATH 1

#endif