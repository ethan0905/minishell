/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 18:49:27 by esafar            #+#    #+#             */
/*   Updated: 2022/04/08 23:32:19 by achane-l         ###   ########.fr       */
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
#include "./get_next_line/get_next_line.h"
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

typedef struct s_quote
{
	int lock;
	bool simpleq;
	bool doubleq;
}			t_quote;

typedef struct s_token
{
	char *str;
	int	type;
	struct s_token	*prev;
	struct s_token	*next;
}			t_token;

typedef struct s_signal
{
	pid_t	pid;
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
	char **test;
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

int		parse(t_data *data, char *str);
void	add_token(t_data *data, char **str);
void	add_char(char **actual, char c);
void	add_char_and_move(t_token *token, char *str, int *j);
void	reset_char(char *c, int *j);
int	check_unclosed_quote(char *str);
void	get_type(t_token *token);
int	ignore_separator(char *str);
void	skip_space(char **str);
bool	is_space(char c);
void	control_c(int code);
void	control_d(int code);

//expands
void	expand_token(t_data *data);
int		check_env(t_data *data, t_token *token, int i);

t_env *create_env(char **env);
char **convert_lst_to_tab(t_data *data);

void	free_tab(char **tab);
void	free_lst(t_data *data);

#endif
