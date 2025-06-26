# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dacastil <dacastil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/24 18:45:56 by daniel-cast       #+#    #+#              #
#    Updated: 2025/06/26 03:24:59 by dacastil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
EXEC = philo
RM = rm -f
FLAGS = -Wall -Wextra -Werror -g3 -I./include  #-fsanitize=address -lpthread
SRC_DIR = ./src
LIBFT = ./libft_bonus/libft.a
INCLUDE_DIR = ./include
SRC = $(SRC_DIR)/checkargs.c		\
		$(SRC_DIR)/free.c 			\
		$(SRC_DIR)/ft_utils.c		\
		$(SRC_DIR)/inits.c			\
		$(SRC_DIR)/main.c			\
		$(SRC_DIR)/routine.c		\
		$(SRC_DIR)/sleep.c			\
		$(SRC_DIR)/update.c		\
		$(SRC_DIR)/utils_macros.c	\

INCLUDE = $(INCLUDE_DIR)/philo.h
OBJS = $(SRC:.c=.o)


all: $(EXEC)

	@echo "              o                          "
	@echo "                   O       /\-.__        "
	@echo "                          /  \�'^|        "
	@echo "             o           T    l  *        "
	@echo "                        _|-..-|_        "
	@echo "                 O    (^ '----' )        "
	@echo "                       \\-....-/^        "
	@echo "             O       o  ) V/ V (        "
	@echo "                       _( (-)  )_        "
	@echo "                   O  /\ )    (  /\        "
	@echo "                     /  \(    ) |  \        "
	@echo "                 o  o    \)  ( /    \        "
	@echo "                   /     |(  )|      \        "
	@echo "                  /    o \ \( /       \        "
	@echo "            __.--'   O    \_ /   .._   \        "
	@echo "           //|)\      ,   (_)   /(((\^)'\        "
	@echo "              |       | O         )  \  |        "
	@echo "              |      / o___      /      /        "
	@echo "             /  _.-''^^__O_^^''-._     /        "
	@echo "           .'  /  -''^^    ^^''-  \--'^        "
	@echo "         .'   .\.  \'''----'''^  . \. \        "
	@echo "       .'    /    '--..____..--'^   \ \        "
	@echo "      /  _.-/                        \ \        "
	@echo "  .::'_/^   |                        |  \.        "
	@echo "         .-'|                        |    '-.        "
	@echo "   _.--'''   \      dacastil         /       \-.        "
	@echo "  /          \                      /           \-._        "
	@echo "  \----..__   \_                  _/_.._   __       \        "
	@echo "           '''''\.              _/      ''^  '''---'^        "
	@echo "                  '-..______..-/                             "


all: $(EXEC)

$(EXEC): $(OBJS) $(LIBFT)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) -o $(EXEC)

%.o: $(SRC_DIR)/%.c $(INCLUDE)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(EXEC)

re: fclean all

:PHONY. draw all clean fclean re
