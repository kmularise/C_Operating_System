#include "pipex.h"

int main()
{
	
	char **a = ft_split("", ' ');
	int i = -1;
	printf("%p", a);

	while(*(a + ++ i))
	{
		printf("i : %d", i);
		printf("%s\n", *(a + i));
	}
}