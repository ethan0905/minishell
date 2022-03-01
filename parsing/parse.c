/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:23:19 by esafar            #+#    #+#             */
/*   Updated: 2022/03/01 16:11:04 by achane-l         ###   ########.fr       */
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

t_token	*add_token(char *str, int *j)
{
	char	c;
	int		i;
	t_token *token;

	i = 0;
	c = ' ';
	token = (t_token *)malloc(sizeof(t_token));
	if(!token)
		return (NULL);
//	if (!token->str)
//		token->str = ft_strdup("");
	token->str = NULL;
	while (str[*j] && (str[*j] != ' ' || c != ' '))
	{
		if (c == ' ' && (str[*j] == '\'' || str[*j] == '\"'))
		{
			c = str[(*j)];
			(*j)++;
		}
		else if (c != ' ' && str[*j] == c)
		{
			c = ' ';
			(*j)++;
		}
		else if (str[*j] == '\\' && (*j)++)
		{
			add_char(&token->str, str[(*j)]);
			(*j)++;
		}
		else
		{
			add_char(&token->str, str[(*j)]);
			(*j)++;
		}
	}
//	printf("token: [%s]\n", token->str);
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
		printf("FREE\n");
	}
}

void	get_type(t_token *token, int sep)
{
	if (ft_strcmp(token->str, "<") == 0 && sep == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->str, "<<") == 0 && sep == 0)
		token->type = HEREDOC;
	else if (ft_strcmp(token->str, ">") == 0 && sep == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->str, ">>") == 0 && sep == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->str, "|") == 0 && sep == 0)
		token->type = PIPE;
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

void	parse(t_data *data, char *str)
{
	t_token *token;

//	if (check_quotes(str) == 0)
//	{
//		printf("Error: syntax error with quotes.\n");
//		free(str);
//		return ;
//	}
	printf("str : [%s]\n", str);
	data->begin = create_token_lst(str);

/*	token = data->begin;
	printf("data->begin: %s\n", token->str);
	while (token && token->next)
	{
		printf("token->str: [%s]\n", token->str);
		printf("token->type: %d\n", token->type);
		token = token->next;
	}
	printf("token->str: [%s]\n", token->str);
	printf("token->type: %d\n", token->type);
	while (token && token->prev)
	{
		printf("token precedent!\n");
		printf("token->str: [%s]\n", token->str);
		token = token->prev;
	}*/
	free_lst(data);
}
