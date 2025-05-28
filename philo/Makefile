SRCS_C = philo.c philo_aux.c philo_aux_1.c philo_frees.c philo_inits.c philo_routines.c philo_routines_1.c

NAME = philo

COMPRESS = ar rcs

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -gdwarf-4

CC = cc

SRCS_DIR = srcs/

OBJS_DIR = objs/

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_C))

OBJS = $(addprefix $(OBJS_DIR), $(SRCS_C:.c=.o))

# for tests ----------------------------------

INPUT = 5 800 200 200 

all: $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

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