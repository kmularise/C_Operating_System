#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFF_SIZE 10

void show_error(char *error_message)
{
	perror(error_message);
	exit(1);
}

char *read_full(int fd)
{
	char *backup;
	char *temp;
	char *buffer;
	int bytes;

	backup = ft_strdup("");
	buffer = malloc(sizeof(char *) * (BUFF_SIZE + 1));
	while (1)
	{
		bytes = read(fd, buffer, BUFF_SIZE);
		if (bytes == - 1)
		{
			free(buffer);
			return (NULL);
		}
		if (bytes == 0)
			break;
		buffer[bytes] = 0;
		temp = backup;
		backup = ft_strjoin(backup, buffer);
		free(temp);
	}
	free(buffer);
	return (backup);
}

int write_full(int fd, char *backup)
{
	int answer;

	answer = write(fd, backup, ft_strlen(backup));
	return (answer);
}

int main()
{
	char *buffer;
	char *backup;
	buffer = malloc(sizeof(char) * (BUFF_SIZE + 1));
	int fd1 = open("test1", O_RDONLY);
	int fd2 = open("test2", O_RDWR | O_CREAT | O_TRUNC, 0777);
	backup = read_full(fd1);
	dup2(1, fd2);
	write_full(fd2, backup);
}