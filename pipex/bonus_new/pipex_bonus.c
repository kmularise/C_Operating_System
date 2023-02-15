#include "pipex_bonus.h"

void set_arg(t_arg *arg, int argc, char **argv, char **envps)
{
    arg->infile_fd = open(argv[1], O_RDONLY);
    if (arg->infile_fd < 0)
        show_error(EXIT_FAILURE, "no such file or directory", argv[1]);
    arg->outfile_fd = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 000644);
    if (arg->outfile_fd < 0)
        show_error(EXIT_FAILURE, "no such file or directory", argv[argc - 1]); 
    arg->paths = get_paths(envps);
    arg->cmd_count = argc - 3;
}

void create_pipes(t_arg *arg)
{
    int i;

    i = 0;
    while (i < arg->pipe_count)
    {
        if (pipe(&(arg->pipes)[2 * i]) < 0)//free
            show_error(EXIT_FAILURE, "pipe production failure", NULL);
        i++;
    }

}

void start_here_doc()
{
    ft_putstr_fd("you need to start!",2);
}

int main(int argc, char **argv, char **envps)
{
    t_arg   arg;

    if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
        start_here_doc();
    arg.pipe_count = 2 * (arg.cmd_count - 1);
    arg.pipes = malloc(sizeof(int) * arg.pipe_count);
    create_pipes(&arg);
    
}