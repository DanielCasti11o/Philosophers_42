# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/24 18:45:56 by daniel-cast       #+#    #+#              #
#    Updated: 2025/03/24 18:58:40 by daniel-cast      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
EXEC = philo
FLAGS = -Wall -Wextra -Werror -g3
SRC_DIR = ./src
INCLUDE_DIR = ./include
SRC = $(wildcard$(SRC_DIR)/*.c)
INCLUDE = $(wildcard$(INCLUDE_DIR)/*.h)

draw :


	@echo "              o                          "
	@echo "                   O       /\-.__        "
	@echo "                          /  \�'^|        "
	@echo "             o           T    l  *        "
	@echo "                        _|-..-|_        "
	@echo "                 O    (^ '----' )        "
	@echo "                       \\-....-/^        "
	@echo "             O       o  ) "/ " (        "
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

#all: $(EXEC)

#$(EXEC) :
:PHONY. draw
