# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/06 17:04:03 by esafar            #+#    #+#              #
#    Updated: 2022/02/28 17:53:42 by achane-l         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = ./main.c \
	./parsing/check_quotes.c \
	./parsing/parse.c \
	./utils/ft_strlen.c \
	./utils/ft_strcmp.c \

CC = cc
R_FLAG = -lreadline
FLAGS = -Wextra -Wall -Werror
INCL = minishell.h

OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${R_FLAG} ${FLAGS} ${OBJS} -I includes -o ${NAME}

clean:
	rm -f ${OBJS}

fclean:
	rm -f ${OBJS} ${NAME}

re:	fclean all

%.o: %.c ${INCL}
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

.PHONY: all clean fclean re
