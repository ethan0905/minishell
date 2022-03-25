/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:23:19 by esafar            #+#    #+#             */
/*   Updated: 2022/03/07 15:49:42 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_lst(t_data *data)
{
	t_token *token;

	while (data->begin)
	{
		token = data->begin;
		if (data->begin->str)
			free(data->begin->str);
		data->begin = data->begin->next;
		if (token)
			free(token);
	}
}

t_token	*add_token(char *str, int *j)
{
	char	c;
	t_token *token;

	c = ' ';
	token = (t_token *)malloc(sizeof(t_token));
	if(!token)
		return (NULL);
	token->str = NULL;
	while (str[*j] && (str[*j] != ' ' || c != ' '))
	{
		if (c == ' ' && (str[*j] == '\'' || str[*j] == '\"'))
		{
			c = str[(*j)];
			(*j)++;
		}
		else if (c != ' ' && str[(*j)] == c)
			reset_char(&c, j);
		else if (str[*j] == '\\' && str[*j + 1] && str[*j + 1] != '$' && (*j)++)
			add_char_and_move(token, str, j);
		else
			add_char_and_move(token, str, j);
		if (str[(*j)] == '|' && (c == '\'' || c == '\"'))
			token->type = ARG;
	}
	return (token);
}

t_token *create_token_lst(char *str)
{
	int i = 0;
	int sep = 0;
	t_token *prev;
	t_token *next;

	prev = NULL;
	next = NULL;
	skip_space(str, &i);
	while (str[i])
	{
		sep = ignore_separator(str, i);
		next = add_token(str, &i);
		next->prev = prev;
		if (prev)
			prev->next = next;
		prev = next;
		get_type(next, sep);
		skip_space(str, &i);
	}
	if (next)
		next->next = NULL;
	while (next && next->prev)
		next = next->prev;
	return (next);
}

int	parse(t_data *data, char *str)
{
//	t_token *token;

	if (ft_strlen(str) == 0)
		return (0);
	if (!check_unclosed_quote(str))
	{
		printf("Error: unclosed quote.\n");
		fflush(stdout);
		return (0);
	}
	data->begin = create_token_lst(str);
/*	token = data->begin;

	while (token)
	{
		printf("token : [%s]\n", token->str);
		token = token->next;
	}*/
	expand_token(data);
//	ft_pwd();
//	ft_env(data->envp);
//	ft_export(data, "");
//	ft_unset(data, "test"); //ajouter le '=' a la fin de la str
/*
	int i = 0;
	while (data->test[i])
	{
		printf("TEST[%d] = %s\n", i, data->test[i]);
		i++;
	}*/
	return (1);
}
