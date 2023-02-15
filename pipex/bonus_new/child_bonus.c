void child_dup2(int read_fd, int write_fd)
{
    dup2(read_fd, 0);
    dup2(write_fd, 1);
}

