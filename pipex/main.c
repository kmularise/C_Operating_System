#include "pipex.h"
#include "parser.c"
#include "finder.c"
//execve - file 2 ㅅㅐ로 쓸 파일
//fork - file 1 새로 생성하는 프로세스 

void memory_leak(void)
{
	system("leaks a.out");
}

void show_error(void)
{
	printf("error!");
	exit(0);
}

int main(int argc, char *argv[], char *envp[]){
	// if (argc != 5)
	// 	show_error();
	//atexit(memory_leak);
	char *s = get_path_env(envp);
	char **paths = ft_split(s, ':');
	char **infile_arg = parse(argv[2], argv[1]);
	char *cmd_path = find_path(infile_arg[0], paths);
	execve(cmd_path, infile_arg, NULL);
	exit(0);
	return 0;
}