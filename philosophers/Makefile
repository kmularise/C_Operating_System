# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/05 09:24:41 by yuikim            #+#    #+#              #
#    Updated: 2023/06/01 20:58:20 by yuikim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = philo
NAME_BONUS = philo_bonus

SRCS_DIR = ./src/
BONUS_DIR = ./bonus/
LIBFT_DIR = ./libft/

SRCS = stack.c\
	stack2.c\
	push_swap.c\
	push_swap_cmd.c\
	algorithm.c\
	push_swap_cmd2.c\
	hard_coding.c\
	push_swap_utils.c\
	bruth_force.c\
	push_swap_utils2.c\
	algorithm2.c\
	hard_coding2.c
SRCS_BONUS = checker_bonus.c\
	checker_utils_bonus.c\
	checker_utils2_bonus.c\
	stack_bonus.c\
	stack2_bonus.c\
	push_swap_cmd_bonus.c\
	push_swap_cmd2_bonus.c
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