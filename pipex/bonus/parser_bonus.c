/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 12:31:27 by yuikim            #+#    #+#             */
/*   Updated: 2023/01/07 17:18:52 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	get_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

void	ft_free_dptr(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	is_empty_string(char *full_cmd)
{
	if (full_cmd[0] == 0)
		return (1);
	return (0);
}

int	is_only_space_string(char *full_cmd)
{
	int	i;

	i = 0;
	while (full_cmd[i])
	{
		if (full_cmd[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

char	**parse(char *full_cmd)
{
	char	**file_arg;
	char	**cmd_arr;
	int		height;
	int		i;

	i = 0;
	if (is_empty_string(full_cmd) || is_only_space_string(full_cmd))
	{
		file_arg = malloc(sizeof(char *) * 2);
		file_arg[0] = full_cmd;
		file_arg[1] = NULL;
		return (file_arg);
	}
	cmd_arr = ft_split(full_cmd, ' ');
	height = get_height(cmd_arr);
	file_arg = malloc(sizeof(char *) * (height + 1));
	while (cmd_arr[i])
	{
		file_arg[i] = cmd_arr[i];
		i++;
	}
	file_arg[height] = NULL;
	free(cmd_arr);
	return (file_arg);
}
