#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
int main()
{
	int fd;
	fd = open("./test1", O_WRONLY);
	write(fd,"true", 4);
	write(1,"true", 4);

}