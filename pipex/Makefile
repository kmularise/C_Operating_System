# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/05 09:24:41 by yuikim            #+#    #+#              #
#    Updated: 2023/01/05 17:24:10 by yuikim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = pipex
NAME_BONUS = pipex_bonus

SRCS_DIR = ./src/
BONUS_DIR = ./bonus/
LIBFT_DIR = ./libft/

SRCS = main.c\
		finder.c\
		parser.c
SRCS_BONUS = main_bonus.c
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
OBJS = ${SRCS:.c=.o}

all : $(NAME)

clean :
	make -C libft clean
	rm -rf $(OBJS) $(OBJS_BONUS)
fclean : clean
	make -C libft fclean
	rm -rf $(NAME) $(NAME_BONUS)

re : fclean all
bonus : $(NAME_BONUS)

$(NAME) : $(OBJS)
	

$(NAME_BONUS) : $(OBJS_BONUS)
	make -C libft all
	$(CC) $(CFLAGS) 
	

# all: make_libft ${NAME}
# make_libft:
# 	make -C libft all
# ${NAME}: ${OBJS}
# 	cp libft/libft.a src/${NAME}
# 	ar r $@ $^
# clean:
# 	make -C src clean
# 	make -C libft clean
# 	rm -rf ${OBJS}
# fclean : clean
# 	make -C libft fclean
# 	rm -rf ${NAME}
# re : fclean all

# bonus : $