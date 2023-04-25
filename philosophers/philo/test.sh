#cc -Wall -Wextra -Werror 
cc -g3 -fsanitize=thread thread.c philosophers.c init.c utils.c utils2.c libft/*.c