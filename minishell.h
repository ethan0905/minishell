/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 18:49:27 by esafar            #+#    #+#             */
/*   Updated: 2022/02/10 18:49:28 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>

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

typedef struct s_token
{
	char *str;
	int	type;
	struct s_token	*prev;
	struct s_token	*next;
}			t_token;

typedef struct s_data
{
	t_token *begin;
	bool end;
}			t_data;

void	parse(t_data *data, char *str);

#endif
