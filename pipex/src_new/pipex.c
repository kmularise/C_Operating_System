#include "pipex.h"

void show_error(int exit_num, char *message, char *filename)
{
	ft_putstr_fd("zsh: ", 2);
	if (message)
		ft_putstr_fd(message, 2);
	if (filename)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(filename, 2);
	}
	ft_putstr_fd("\n", 2);
	exit(exit_num);
}

int main(int argc, char **argv, char **envp)
{
	int		**pipes;
	t_arg	arg;//구조체 정의
	// extern int errno;

	//errno = 0;
	init_arg(&arg, argc, argv, envp);
}