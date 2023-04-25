#cc -Wall -Wextra -Werror 
cc -fsanitize=thread -g3 thread.c philosophers.c init.c utils.c utils2.c libft/*.c