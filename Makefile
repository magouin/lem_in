# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: magouin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/17 19:23:46 by magouin           #+#    #+#              #
#    Updated: 2016/05/06 17:42:22 by magouin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_NAME = main.c \
		   get_next_line/get_next_line.c \
		   finish.c \
		   resolve.c \
		   ex.c \
		   ex2.c \
		   ex3.c \
		   ex4.c \
		   ex5.c

OBJ_PATH = ./obj/

INC_PATH = ./ft_printf/

NAME = lem-in

CC = gcc

CFLAGS = -Werror -Wextra -Wall

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I, $(INC_PATH))

all : $(NAME)

$(NAME):
	make -C ft_printf
	$(CC) $(CFLAGS) $(INC) -o $(NAME) $(SRC_NAME) ft_printf/libftprintf.a

clean:
	make -C ft_printf clean
	rm -fv $(OBJ)
	
fclean: clean
	rm -fv $(NAME)
	make -C ft_printf fclean

re: fclean all

.PHONY : all clean fclean re
