/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:27:48 by yuikim            #+#    #+#             */
/*   Updated: 2023/02/17 22:03:27 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

t_fd_list	*read_fd_node(t_fd_list *current_fd_node, t_fd_list **head, int fd)
{
	char	*buffer;
	ssize_t	byte;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (1)
	{
		byte = read(fd, buffer, BUFFER_SIZE);
		if (byte == -1)
		{
			free(buffer);
			remove_node(current_fd_node, head);
			return (NULL);
		}
		if (byte == 0)
			break ;
		buffer[byte] = 0;
		current_fd_node->backup = gnl_strjoin(current_fd_node->backup, buffer);
		if (gnl_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (current_fd_node);
}

char	*extract_line(t_fd_list *node)
{
	size_t	i;
	char	*line;

	i = 0;
	while ((node->backup)[i] && (node->backup)[i] != '\n')
		i++;
	if (!(node->backup)[i] || i + 1 == gnl_strlen(node->backup))
	{
		line = gnl_strjoin(NULL, node->backup);
		free(node->backup);
		node->backup = NULL;
		return (line);
	}
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	gnl_strlcpy(line, node->backup, i + 2);
	gnl_strlcpy(node->backup, node->backup + i + 1,
		gnl_strlen(node->backup) - i + 1);
	return (line);
}

char	*get_next_line(int fd)
{	
	char				*line;
	static t_fd_list	*head;
	t_fd_list			*current_fd_node;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	current_fd_node = find_node(&head, fd);
	if (!current_fd_node)
		return (NULL);
	current_fd_node = read_fd_node(current_fd_node, &head, fd);
	if (!current_fd_node)
		return (NULL);
	if (!(current_fd_node->backup))
	{
		remove_node(current_fd_node, &head);
		return (NULL);
	}
	line = extract_line(current_fd_node);
	return (line);
}

t_fd_list	*find_node(t_fd_list **head, int fd)
{
	t_fd_list	*temp;

	if (!(*head))
	{
		*head = new_fd_node(fd);
		return (*head);
	}
	temp = *head;
	while (temp)
	{
		if (temp->fd == fd)
			return (temp);
		if (!temp->next)
			break ;
		temp = temp->next;
	}
	temp->next = new_fd_node(fd);
	return (temp->next);
}

void	remove_node(t_fd_list *curr_node, t_fd_list **head)
{
	t_fd_list	*temp;

	if (*head == NULL || curr_node == NULL)
		return ;
	temp = *head;
	if (curr_node == *head)
		*head = (*head)->next;
	else
	{
		while (temp->next)
		{
			if (temp->next == curr_node)
				break ;
			temp = temp->next;
		}
		if (!curr_node->next)
			temp->next = NULL;
		else
			temp->next = curr_node->next;
		temp = curr_node;
	}
	free(temp->backup);
	free(temp);
}
