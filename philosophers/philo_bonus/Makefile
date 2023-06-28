# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/05 09:24:41 by yuikim            #+#    #+#              #
#    Updated: 2023/06/07 11:05:47 by yuikim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = philo_bonus

SRCS_DIR = ./

SRCS = child_bonus.c\
	init_bonus.c\
	philosophers_bonus.c\
	utils_bonus.c\
	utils2_bonus.c\
	utils3_bonus.c
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
SRCS_PATH = $(addprefix $(SRCS_DIR), $(SRCS))
OBJS = ${SRCS_PATH:.c=.o}

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus :	$(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME_BONUS)

clean :
	rm -rf $(OBJS) $(OBJS_BONUS)
fclean : clean
	rm -rf $(NAME) $(OBJS) $(OBJS_BONUS)

re :
	make fclean
	make all
	
.PHONY:		all clean fclean bonus re