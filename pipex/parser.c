# include "pipex.h"

int get_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}
char **parse(char *full_cmd, char *file)//옵션 두개 이상 있는 경우 수정할 필요가 있음
{
	char **file_arg;
	char **cmd_arr;
	int height;
	int i;

	cmd_arr = ft_split(full_cmd, ' ');
	height = get_height(cmd_arr);
	file_arg = malloc(sizeof(char *) * (height + 2));
	i = 0;
	while (cmd_arr[i])
	{
		file_arg[i] = cmd_arr[i];
		i++;
	}
	// file_arg[0] = cmd_arr[0];
	// file_arg[1] = cmd_arr[1];
	file_arg[2] = file;
	file_arg[3] = NULL;
	free(cmd_arr);
	return (file_arg);
}
