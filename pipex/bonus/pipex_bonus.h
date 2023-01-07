# ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

#define START 0
#define LAST -1

#include "../libft/libft.h"



int		is_path_env(char *envp);
char	*get_path_env(char *envps[]);
char	*find_path(char *cmd, char **paths);

int		get_height(char **map);
void	ft_free_dptr(char **map);
int		is_empty_string(char *full_cmd);
int		is_only_space_string(char *full_cmd);
char	**parse(char *full_cmd);

int	open_file_and_control_cmd(int pipes[2], char **argv, char **envp);

int	control_cmd_and_write_file(int pipes[2], char **argv, char **envp);
int	control_pipe_and_cmd(int pre_pipes[2], int cmd_count,
	char **argv, char **envp);
int	control_pipe_and_cmd2(int pre_pipes[2], int cmd_count,
	char **argv, char **envp);
// int	send_pipe(int pipes[2], int pre_pipes[2], char *cmd, char **envp);
// int	get_pipe(int pipes[2], int pre_pipes[2], char *cmd, char **envp);
int	connect_pipe(int pipes[2], int pre_pipes[2], char *cmd, char **envp);
int	connect_pipe2(int pipes[2], int pre_pipes[2], char *cmd, char **envp);

void	show_error(char *error_message);

#include "../libft/ft_substr.c"
#include "../libft/ft_split.c"
#include "../libft/ft_strjoin.c"
#include "../libft/ft_strlen.c"
#include "../libft/ft_strdup.c"
#include "finder_bonus.c"
#include "parser_bonus.c"
#include "pipex_utils_bonus.c"


// # ifndef BUFFER_SIZE
// # define BUFFER_SIZE 42
// # endif

#endif