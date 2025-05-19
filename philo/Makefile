# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/16 20:18:20 by gvon-ah-          #+#    #+#              #
#    Updated: 2025/05/19 17:53:15 by gvon-ah-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_C = philo.c

NAME = philo

COMPRESS = ar rcs

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -gdwarf-4

CC = cc

SRCS_DIR = srcs/

OBJS_DIR = objs/

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_C))

OBJS = $(addprefix $(objs), $(SRCS_C:.c=.o))

# for tests ----------------------------------

INPUT = 5 800 200 200 

all: $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c | $(OBJS_DIR)
	@$(cc) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo $(NAME) Compiled!

clean:
	@if [ -d $(OBJS_DIR) ]; then $(RM) $(OBJS_DIR); fi
	@echo Clean objs!

fclean: clean
	@$(RM) $(NAME) philo
	@echo Clean all!

re: fclean all

val: $(NAME)
	@make re
	@clear
	valgrind --leak-check=full ./$(NAME) $(INPUT)

.PHONY: all fclean clean re val