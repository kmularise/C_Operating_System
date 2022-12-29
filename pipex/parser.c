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

	i = 0;
	while (envps[i])
	{
		if (is_path_env(envps[i]))
			return (envps[i]);
		i++;
	}
	return (NULL);
}

void ft_dptr_free(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	*find_path(char *cmd, char **paths)
{
	int i;
	int mode;
	char *cmd_path;

	i = 0;
	mode = F_OK;
	while (paths[i])
	{
		//cmd_path = ft_strjoin(paths[i], cmd);
		if (access(cmd_path, mode) == 0)
		{
			//ft_dptr_free(paths);
			return paths[i];//(cmd_path);
		}
		i++;
	}
	//ft_dptr_free(paths);
	return (NULL);
}//못찾으면 NULL반환