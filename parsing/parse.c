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
#include <unistd.h>

void	skip_space(char *str, int *i)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\n' || str[*i] == '\r' || str[*i] == '\f' || str[*i] == '\t' || str[*i] == '\v'))
		(*i)++;
}

int	ignore_separator(char *str, int i)
{
	if (str[i] && str[i] == '\\' && str[i+1] && str[i+1] == '|')
		return (1);
	else if (str[i] && str[i] == '\\' && str[i+1] && str[i+1] == '>')
	{
		if (str[i+2] && str[i+2] == '>')
			return (1);
	}
	else if (str[i] && str[i] == '\\' && str[i+1] && str[i+1] == '>' && str[i+2] && str[i+2] == '>')
		return (1);
	else if (str[i] && str[i] == '\\' && str[i+1] && str[i+1] == ';')
		return (1);
	else if (str[i] && str[i] == '\\' && str[i+1] && str[i+1] == '$')
		return (1);
	return (0);
}

void	add_char(char **actual, char c)
{
	int i;
	char *dest;

	dest = (char *)malloc(sizeof(char) * (ft_strlen(*actual) + 2));
	if (!dest)
		return ;
	i = 0;
	while ((*actual) && (*actual)[i] != '\0')
	{
		dest[i] = (*actual)[i];
		i++;
	}
	dest[i] = c;
	dest[i + 1] = '\0';
	if (*actual)
		free(*actual);
	(*actual) = dest;
}

void	add_char_and_move(t_token *token, char *str, int *j)
{
	add_char(&token->str, str[(*j)]);
	(*j)++;
}

void	reset_char(char *c, int *j)
{
	(*c) = ' ';
	(*j)++;
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
//		printf("FREE\n");
	}
}

void	get_type(t_token *token, int sep)
{
//	printf("token->str: %s\n", token->str);
	if (ft_strcmp(token->str, "<") == 0 && sep == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->str, "<<") == 0 && sep == 0)
		token->type = HEREDOC;
	else if (ft_strcmp(token->str, ">") == 0 && sep == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->str, ">>") == 0 && sep == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->str, "|") == 0 && token->type != ARG && sep == 0)
		token->type = PIPE;
	else if (ft_strcmp(token->str, "$") == 0 && sep == 0)
		token->type = DOLLAR;
	else if (token->prev == NULL || token->prev->type == PIPE) //temporaire
		token->type = CMD;
	else
		token->type = ARG;
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

int	check_unclosed_quote(char *str)
{
	int i;
	int lock;
	bool simpleq;
	bool doubleq;

	i = 0;
	simpleq = false;
	doubleq = false;
	lock = 0;
	while (str[i])
	{
//		printf("str[%d] = [%c]\n", i, str[i]);
		if (lock == 0 && (str[i] == '\'' || str[i] == '\"') && (str[i-1] && str[i-1] != '\\'))
		{
			if (str[i] == '\'')
			{
				simpleq = !simpleq;
//				printf("OPEN simple\n");
			}
			else if (str[i] == '\"')
			{
				doubleq = !doubleq;
//				printf("OPEN double\n");
			}
			lock = 1;
//			printf("OPEN\n");
		}
		else if (lock == 1 && ((str[i] == '\'' && simpleq ) || (str[i] == '\"' && doubleq)) && (str[i-1] && str[i-1] != '\\'))
		{
			if (simpleq && str[i] == '\'')
			{
				simpleq = !simpleq;
//				printf("CLOSED simple\n");
			}
			else if (doubleq && str[i] == '\"')
			{
				doubleq = !doubleq;
//				printf("CLOSED double\n");
			}
			lock = 0;
//			printf("CLOSED\n");
		}
		i++;
	}
	if (simpleq || doubleq)
		return (0);
	return (1);
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
//	ft_export(data, "test=\"TEST\"");
//	ft_export(data, "ABC=\"ABC\"");
//	ft_export(data, "LALA=\"LALA\"");
	//ft_env(data->test);
//	printf("\n");
//	ft_unset(data, "TERM_SESSION_ID"); //ajouter le '=' a la fin de la str
//	ft_unset(data, "TERM_SESSION_ID"); //ajouter le '=' a la fin de la str
//	ft_unset(data, "LALA"); //ajouter le '=' a la fin de la str
//	ft_unset(data, "ABC"); //ajouter le '=' a la fin de la str
//	ft_unset(data, "test"); //ajouter le '=' a la fin de la str
	//ft_unset(data, "LESS=-R"); //ajouter le '=' a la fin de la str
/*
	int i = 0;
	while (data->test[i])
	{
		printf("TEST[%d] = %s\n", i, data->test[i]);
		i++;
	}*/
	return (1);
}
