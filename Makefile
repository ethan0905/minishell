# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/06 17:04:03 by esafar            #+#    #+#              #
#    Updated: 2022/05/18 19:26:49 by achane-l         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = ./main.c \
	./parsing/parse_utils.c \
	./parsing/parse.c \
	./parsing/get_token_str.c \
	./parsing/special_char_utils.c \
	./parsing/token_list.c \
	./parsing/signal.c \
	./parsing/expand.c\
	./expand/expand.c \
	./utils/ft_strlen.c \
	./utils/ft_strcmp.c \
	./utils/ft_strncmp.c \
	./utils/ft_strdup.c \
	./utils/ft_strjoin.c \
	./utils/ft_split.c \
	./utils/ft_strcopy.c \
	./utils/ft_itoa.c \
	./utils/ft_putstr_fd.c \
	./utils/env_utils.c \
	./built-in/ft_pwd.c \
	./built-in/ft_env.c \
	./built-in/ft_echo.c \
	./built-in/ft_export.c \
	./built-in/ft_unset.c \
	./built-in/ft_cd.c \
	./built-in/ft_exit.c \
	./exec_files/exec.c \
	./exec_files/get_cmds.c \
	./exec_files/get_files.c \
	./exec_files/init_cmds.c \
	./exec_files/paths.c \
	./exec_files/process.c \
	./get_next_line/get_next_line.c \

CC = cc -g3
R_FLAG = -lreadline
FLAGS = -Wextra -Wall -Werror
INCL = minishell.h

OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${FLAGS} ${OBJS} -I includes -L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include -o ${NAME} ${R_FLAG}

clean:
	rm -f ${OBJS}

fclean:
	rm -f ${OBJS} ${NAME}

re:	fclean all

%.o: %.c ${INCL}
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

.PHONY: all clean fclean re
