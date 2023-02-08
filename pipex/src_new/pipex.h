# ifndef PIPEX_H
# define PIPEX_H

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

#include "libft/libft.h"
typedef struct	s_arg {
	int cmd_count;
	char *infile;
	char *outfile;
	char ***cmds;
	char **envp;
	char **paths;
}	t_arg;

void show_error(int exit_num, char *message, char *filename);

// #include "libft/ft_substr.c"
// #include "libft/ft_split.c"
// #include "libft/ft_strjoin.c"
// #include "libft/ft_strlen.c"
// #include "libft/ft_strdup.c"

// # ifndef BUFFER_SIZE
// # define BUFFER_SIZE 42
// # endif

#endif