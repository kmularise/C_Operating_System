#include "pipex.h"
#include "parser.c"
//execve - file 2 ㅅㅐ로 쓸 파일
//fork - file 1 새로 생성하는 프로세스 

void a(void)
{
	system("leaks a.out");
}
int main(int argc, char *argv[], char *envp[]){
	atexit(a);
	// int i = 0;
	// while (envp[i] != NULL)
	// {
	// 	printf("%s\n", envp[i]);
	// 	i++;
	// }
	char *s = get_path_env(envp);
	//printf("%s", s);
	char **paths = ft_split(s, ':');
	//char *file_path = find_path("ls", paths);
	printf("%s\n", paths[0]);
	// int i = 0;
	// while (paths[i])
	// {
	// 	printf("%s\n", paths[i]);
	// 	i++;
	// }
	//system("leaks a.out");
	exit(0);
	return 0;
}