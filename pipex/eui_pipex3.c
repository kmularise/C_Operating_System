#include "pipex.h"
#include "parser.c"
#include "finder.c"
//execve - file 2 ㅅㅐ로 쓸 파일
//fork - file 1 새로 생성하는 프로세스 

// void memory_leak(void)
// {
// 	system("leaks a.out");
// }

// void show_error(char *error_message)
// {
// 	perror(error_message);
// 	exit(1);
// }

// int do_infile_process(int pipes[2], char **argv, char **envp, pid_t pid)
// {

// 	//sprintf(buff, "check 일방향 통신\n");
// 	char *s = get_path_env(envp);
// 	char **paths = ft_split(s, ':');
// 	char **infile_arg = parse(argv[2], argv[1]);
// 	char *cmd_path = find_path(infile_arg[0], paths);
// 	int fd0 = open(argv[1], O_RDONLY);
// 	dup2(fd0,0);
// 	execve(cmd_path, infile_arg, NULL);
// 	printf("자식 프로세스");
// 	return (0);
// }

// int do_outfile_process(int pipes[2], char *backup, pid_t pid)
// {
// 	int fd2 = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
// 	printf("부모 프로세스");
// 	return (0);
// }

int main(int argc, char *argv[], char *envp[]){
	int pipes[2];
	char *backup;
	pid_t pid;
	// if (argc != 5)
	// 	show_error("invalid input!");
	//atexit(memory_leak);
	char *s = get_path_env(envp);
	char **paths = ft_split(s, ':');
	char **infile_arg = parse(argv[2], argv[1]);
	char *cmd_path = find_path(infile_arg[0], paths);
	int fd1 = open(argv[1], O_RDONLY);
	int fd2 = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	dup2(fd1,0);
	dup2(fd2, 1);
	//execve(cmd_path, infile_arg, NULL);//process 2개로 execve

	// if (pipe(pipes) == -1)
	// 	show_error("파이프 생성 실패");
	// pid = fork();
	// if (pid == -1)
	// 	show_error("자식 프로세스 생성 실패");
	// else if (pid == 0)
	// 	do_infile_process(pipes, argv, envp, pid);
	// else
	// 	do_outfile_process(pipes, backup, pid);
 
	exit(0);
	return 0;
}