#include "pipex.h"

char	**get_paths(char **envps)
{
	int	i;
	char	**paths;

	i = 0;
	while (envps[i])
	{
		if (ft_strncmp(envps[i], "PATH=", 5) == 0)
			break;
		i++;
	}
	paths = ft_split(&envps[i][5], ':');
	return (paths);
}

void init_arg(t_arg *arg, int argc, char **argv, char **envp)
{
	if (argc != 5)
		show_error(EXIT_FAILURE, "The number of arguments is wrong.", NULL);
	arg->paths = get_paths(envp);
	arg->envp = envp;
	arg->infile = argv[1];
	arg->cmd_count = argc - 3;
	arg->outfile = argv[argc - 1];
	arg->cmds = &argv[2];
	// arg->cmds = 

}