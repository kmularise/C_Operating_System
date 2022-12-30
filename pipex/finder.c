#include "pipex.h"

int	is_path_env(char *envp)
{
	if (envp[0] != 'P')
		return (0);
	if (envp[1] != 'A')
		return (0);
	if (envp[2] != 'T')
		return (0);
	if (envp[3] != 'H')
		return (0);
	if (envp[4] != '=')
		return (0);
	return (5);
}

char	*get_path_env(char *envps[])
{
	int	i;
	char	*answer;

	i = 0;
	while (envps[i])
	{
		if (is_path_env(envps[i]))
		{
			answer = ft_substr(envps[i], 5, ft_strlen(envps[i]) - 5);
			return (answer);
		}
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char **paths)
{
	int i;
	char *cmd_path;
	char *temp;

	i = 0;
	cmd_path = NULL;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], "/");
		temp = cmd_path;
		cmd_path = ft_strjoin(cmd_path, cmd);
		free(temp);
		if (access(cmd_path, F_OK) == 0)
			break ;
		i++;
	}
	return cmd_path;
}