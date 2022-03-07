# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/06 17:04:03 by esafar            #+#    #+#              #
#    Updated: 2022/03/01 16:53:17 by achane-l         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = ./main.c \
	./parsing/check_quotes.c \
	./parsing/parse.c \
	./parsing/signal.c \
	./expand/expand.c \
	./utils/ft_strlen.c \
	./utils/ft_strcmp.c \
	./utils/ft_strdup.c \
	./utils/ft_strjoin.c \
	./utils/ft_itoa.c \
	./built-in/ft_pwd.c \
	./built-in/ft_env.c \

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
