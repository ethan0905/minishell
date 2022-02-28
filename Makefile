# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esafar <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/06 17:04:03 by esafar            #+#    #+#              #
#    Updated: 2022/02/08 17:15:28 by esafar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = ./main.c \
<<<<<<< HEAD
	./parsing/add_char.c \
	./parsing/do_cmd.c \
	./parsing/lst_utils.c \
	./parsing/remove_space.c \
	./utils/ft_strlen.c \
=======
	./parsing/check_quotes.c \
	./parsing/parse.c
>>>>>>> ethan

CC = clang
FLAGS = -lreadline #-fsanitize=address #-Wextra -Wall -Werror
INCL = minishell.h

OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${FLAGS} ${OBJS} -I includes -o ${NAME}

clean:
	rm -f ${OBJS}

fclean:
	rm -f ${OBJS} ${NAME}

re:	fclean all

%.o: %.c ${INCL}
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

.PHONY: all clean fclean re
