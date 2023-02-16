#include "pipex_bonus.h"

char	*get_cmd_path(char *cmd, char **paths)
{
	int i;
	char *cmd_path;
	char *temp;

	i = 0;
	cmd_path = NULL;
	if (!cmd)
		(NULL);
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], "/");
		temp = cmd_path;
		cmd_path = ft_strjoin(cmd_path, cmd);
		free(temp);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	if (access(cmd, F_OK) == 0)
		return (cmd);
	return (NULL);
}

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

void show_error(int exit_num, char *message1, char *message2)
{
	ft_putstr_fd("zsh: ", 2);
	if (message1)
		ft_putstr_fd(message1, 2);
	if (message2)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(message2, 2);
	}
	ft_putstr_fd("\n", 2);
	exit(exit_num);
}
