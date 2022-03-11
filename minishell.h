/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 18:49:27 by esafar            #+#    #+#             */
/*   Updated: 2022/03/01 17:14:03 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <signal.h>
#include "./utils/utils.h"


# include <limits.h>

//# define PURPLE \033[0;35m
// # define YELLOW \033[0;33m
// # define END \033[0;m

# define INPUT 		1	//"<"
# define HEREDOC 	2	//"<<"
# define TRUNC 		3	//">"
# define APPEND 	4	//">>"
# define PIPE 		5	//"|"
# define CMD 		6	//"|"
# define ARG 		7	//"|"
# define DOLLAR 	8	//"$"

pid_t pid;

typedef struct s_token
{
	char *str;
	int	type;
	struct s_token	*prev;
	struct s_token	*next;
}			t_token;

typedef struct s_signal
{
	int lol;
}			t_signal;

typedef struct s_env
{
	char	*line;
	struct s_env *prev;
	struct s_env *next;
}			t_env;

typedef struct s_data
{
	t_token *begin;
	t_env *env;
	t_signal signal;
	char **envp;
	struct s_cmd	*cmd;
	bool end;
	int	exit_code;
}			t_data;

#include "./exec_files/exec_files.h"
#include "./built-in/built-in.h"

typedef struct s_expand
{
	char	*line;
	char	*dest;
	char	*expand;
	int		expand_or_not;
}			t_expand;

void	parse(t_data *data, char *str);
void	control_c(int code);
void	control_d(int code);

//expands
void	expand_token(t_data *data);
int		check_env(t_data *data, t_token *token, int i);

void	add_char(char **actual, char c);
void	free_lst(t_data *data);

extern t_signal sig;
#endif
