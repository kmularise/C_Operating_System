# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/05 09:24:41 by yuikim            #+#    #+#              #
#    Updated: 2023/02/17 22:00:35 by yuikim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = pipex
NAME_BONUS = pipex

SRCS_DIR = ./src/
BONUS_DIR = ./bonus/
LIBFT_DIR = ./libft/

SRCS = child.c\
		pipex.c
SRCS_BONUS = pipex_bonus.c\
			child_bonus.c\
			pipex_utils_bonus.c\
			pipex_file_bonus.c
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
SRCS_PATH = $(addprefix $(SRCS_DIR), $(SRCS))
SRCS_BONUS_PATH = $(addprefix $(BONUS_DIR), $(SRCS_BONUS))
OBJS = ${SRCS_PATH:.c=.o}
OBJS_BONUS = ${SRCS_BONUS_PATH:.c=.o}

all : $(NAME)

$(NAME) : $(OBJS)
	make -C libft all
	$(CC) $(CFLAGS) $(OBJS) libft/libft.a -o $(NAME)

bonus :	$(OBJS_BONUS)
	make -C libft all
	$(CC) $(CFLAGS) $(OBJS_BONUS) libft/libft.a -o $(NAME)

clean :
	make -C libft clean
	rm -rf $(OBJS) $(OBJS_BONUS)
fclean : clean
	make -C libft fclean
	rm -rf $(NAME) $(OBJS) $(OBJS_BONUS)

re :
	make fclean
	make all
	
.PHONY:		all clean fclean bonus re