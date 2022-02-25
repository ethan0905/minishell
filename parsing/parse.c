/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:23:19 by esafar            #+#    #+#             */
/*   Updated: 2022/02/08 19:05:33 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen(char const *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str != c)
	{
		if (*str == '\0')
		{
			return (NULL);
		}
		str++;
	}
	return (str);
}

char	*ft_strdup(char *src)
{
	size_t	i;
	char	*dest;

	i = 0;
	dest = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!dest)
		return (NULL);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

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
		return (1);
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
//	token->str = (char *)malloc(sizeof(char) * token_alloc(str, i)); //get the good alloc size
	if (!token->str)
		token->str = ft_strdup("");
	while (str[*j] && (str[*j] != ' ' || c != ' '))
	{
		if (c == ' ' && (str[*j] == '\'' || str[*j] == '\"'))
			c = str[(*j)++];
		else if (c != ' ' && str[*j] == c)
		{
			c = ' ';
			(*j)++;
		}
		else if (str[*j] == '\\' && (*j)++)
		{
			add_char(&token->str, str[(*j)++]);
//			(*j)++;
		}
		else
		{
			add_char(&token->str, str[(*j)++]);
//			(*j)++;
		}
//		printf("addchar: [%s]\n", token->str);
//		else if (str[*j] == '\\' && (*j)++)
//			token->str[i++] = add_char(str[(*j)++]);
//		else
//			token->str[i++] = add_char(str[(*j)++]);

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
		skip_space(str, &i);
	}

	return (next);
}

void	parse(t_data *data, char *str)
{
	t_token *token;

	if (check_quotes(str) == 0)
	{
		printf("Error: syntax error with quotes.\n");
//		free(str);
		return ;
	}
	printf("str : [%s]\n", str);
	data->begin = create_token_lst(str);
	while (data->begin && data->begin->next)
	{
		printf("token: [%s]\n", data->begin->str);
		data->begin = data->begin->next;
	}
}
