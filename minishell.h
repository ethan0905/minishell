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

typedef struct s_lst
{
	char *tmp; //help us for our tests
	bool begin;
	bool end;
	char *infile;
	char *outfile;
	int	redirect[2][2];
	char **cmd;
	struct s_lst *next;
}			t_lst;

typedef struct s_data
{
	size_t	nb_cmd;
	t_lst	*lst_cmd;
}				t_data;

#endif
