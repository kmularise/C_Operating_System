#cc -Wall -Wextra -Werror 
cc -fsanitize=thread -g3 thread.c philosophers.c init.c utils.c utils2.c utils3.c main.c
# cc thread.c philosophers.c init.c utils.c utils2.c libft/*.c main.c