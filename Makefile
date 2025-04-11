# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/24 18:45:56 by daniel-cast       #+#    #+#              #
#    Updated: 2025/04/09 20:06:37 by daniel-cast      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
EXEC = philo
RM = rm -f
FLAGS = -Wall -Wextra -Werror -g3 -I./include # -fsanitize=address
SRC_DIR = ./src
LIB_DIR = ./libft_bonus
INCLUDE_DIR = ./include
SRC = $(wildcard $(SRC_DIR)/*.c)
INCLUDE = $(wildcard $(INCLUDE_DIR)/*.h)
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

$(EXEC) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(EXEC)
	$(MAKE) -C $(LIB_DIR)

%.o: $(SRC_DIR)/%.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIB_DIR) clean

fclean:
	@$(RM) $(OBJS) $(EXEC) > /dev/null 2>&1
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

:PHONY. draw all clean fclean re
