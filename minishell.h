/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 18:49:27 by esafar            #+#    #+#             */
/*   Updated: 2022/05/24 13:35:15 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <signal.h>
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

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}			t_token;

typedef struct s_signal
{
	bool	heredoc;
	pid_t	pid;
}			t_signal;

typedef struct s_env
{
	char			*line;
	struct s_env	*prev;
	struct s_env	*next;
}			t_env;

typedef struct s_data
{
	t_token			*begin;
	t_env			*env;
	t_signal		signal;
	char			**envp;
	char			**test;
	struct s_cmd	*cmd;
	bool			end;
	int				exit_code;
}			t_data;

//expands
char	*expand_str(t_data *data, char *str);
// get token str
void	get_token_str(t_token *token, char **line);
void	get_type(t_token *token);
bool	quoting_gest(char c, bool \
*is_in_single_quote, bool *is_in_double_quote);
//token lst
bool	create_token_lst(t_data *data, char *str);
void	free_token_lst(t_data *data);
//parse utils
char	*my_getenv(t_data *data, char *expand_to_search);
int		check_unclosed_quote(char *str);
void	add_char(char **actual, char c);
//parse
int		parse(t_data *data, char *str);
//signal
void	control_c(int code);
//special char utils
bool	is_space(char c);
void	skip_space(char **str);
bool	is_special_char(char *str);
char	*get_special_char(char **str);

extern t_signal	g_signal;

#endif
