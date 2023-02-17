CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
SRCS = ft_putstr_fd.c ft_split.c ft_strjoin.c ft_strlen.c\
		ft_strncmp.c ft_substr.c get_next_line.c get_next_line_utils.c
OBJS = ${SRCS:.c=.o}
SRCS_B = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c\
		ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
OBJS_B = ${SRCS_B:.c=.o}

ifdef WITH_B
	OBJ_FILES = $(OBJS) 
else
	OBJ_FILES = $(OBJS)
endif

all : $(NAME)

$(NAME) : $(OBJ_FILES)
	ar rc $@ $^

bonus :
	make WITH_B=1 all
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJS) $(OBJS_B)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re bonus