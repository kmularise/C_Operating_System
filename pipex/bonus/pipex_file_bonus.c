/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:13:56 by yuikim            #+#    #+#             */
/*   Updated: 2023/02/17 21:14:08 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	get_infile_fd(t_arg *arg, char **argv)
{
	if (arg->is_here_doc)
		arg->infile_fd = open(".here_doc_tmp", O_RDONLY);
	else
	{
		arg->infile_fd = open(argv[1], O_RDONLY);
		if (arg->infile_fd < 0)
			show_error(EXIT_FAILURE, "no such file or directory", argv[1]);
	}
	return (arg->infile_fd);
}

int	get_outfile_fd(t_arg *arg, char **argv)
{
	arg->outfile_fd = open(argv[arg->cmd_count + arg->is_here_doc + 2],
			O_TRUNC | O_CREAT | O_RDWR, 0644);
	return (arg->outfile_fd);
}

