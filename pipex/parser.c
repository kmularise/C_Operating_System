# include "pipex.h"

char **parse(char *full_cmd, char *file)//옵션 두개 이상 있는 경우 수정할 필요가 있음
{
	char **file_arg;
	char **cmd_arr;

	file_arg = malloc(sizeof(char *) * 4);
	cmd_arr = ft_split(full_cmd, ' ');
	file_arg[0] = cmd_arr[0];
	file_arg[1] = cmd_arr[1];
	file_arg[2] = file;
	file_arg[3] = NULL;
	free(cmd_arr);
	return (file_arg);
}
