# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/05 09:24:41 by yuikim            #+#    #+#              #
#    Updated: 2023/06/01 20:36:27 by yuikim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = philo

SRCS_DIR = ./
LIBFT_DIR = ./libft/

SRCS = init.c\
	main.c\
	philosophers.c\
	thread.c\
	utils.c\
	utils2.c
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
SRCS_PATH = $(addprefix $(SRCS_DIR), $(SRCS))
OBJS = ${SRCS_PATH:.c=.o}

all : $(NAME)

$(NAME) : $(OBJS)
	make -C libft all
	$(CC) $(CFLAGS) $(OBJS) libft/libft.a -o $(NAME)

bonus :	$(OBJS_BONUS)
	make -C libft all
	$(CC) $(CFLAGS) $(OBJS_BONUS) libft/libft.a -o $(NAME_BONUS)

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