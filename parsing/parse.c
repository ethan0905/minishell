/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:23:19 by esafar            #+#    #+#             */
/*   Updated: 2022/04/13 12:33:43 by achane-l         ###   ########.fr       */
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



bool	is_special_char(char *str)
{
	if (str && ft_strlen(str) >= 2)
	{
		if (ft_strncmp(str, "<<", 2) == 0)
			return (true);
		else if (ft_strncmp(str, ">>", 2) == 0)
			return (true);
	}
	if (str && ft_strlen(str) >= 1)
	{
		if (ft_strncmp(str, "<", 1) == 0)
			return (true);
		else if (ft_strncmp(str, ">", 1) == 0)
			return (true);
		else if (ft_strncmp(str, "|", 1) == 0)
			return (true);
		else if (ft_strncmp(str, " ", 1) == 0)
			return (true);
	}
	return (false);
}

char	*get_special_char(char **str)
{
	char	*special_char;

	special_char = NULL;
	if (ft_strncmp(*str, "<<", 2) == 0)
		special_char = ft_strdup("<<");
	else if (ft_strncmp(*str, ">>", 2) == 0)
		special_char = ft_strdup(">>");
	else if (ft_strncmp(*str, "<", 1) == 0)
		special_char = ft_strdup("<");
	else if (ft_strncmp(*str, ">", 1) == 0)
		special_char = ft_strdup(">");
	else if (ft_strncmp(*str, "|", 1) == 0)
		special_char = ft_strdup("|");
	*str = (*str) + ft_strlen(special_char);
	return (special_char);
}

void	expand(t_data *data, t_token *token, char **line, bool is_in_double_quote)
{
	char *expand_to_search;
	char	*expand_value;
	char	*str;
	char	*tmp;

	str = *line;
	//expand_to_search = ft_strdup("");
	expand_value = NULL;
	tmp = NULL;
	if (*(str + 1) == '\'' || * (str + 1) == '\"')
		return ;
	if (*(str + 1) == '?')
	{
		expand_value = ft_itoa(data->exit_code);
		str++;
	}
	else
	{
		expand_to_search = ft_strdup("");
		if (is_in_double_quote)
		{
			str++;
			while (*str != '\"')
			{
				add_char(&expand_to_search, *str);
				str++;
			}
		}
		else
		{
			while (*(str + 1) && (!is_special_char(str + 1) || !is_space(*(str + 1))))
			{
				add_char(&expand_to_search, *(str + 1));
				str++;
			}
		}
		if (expand_to_search)
		{
			expand_value = getenv(expand_to_search);
			if (expand_value)
				expand_value = ft_strdup(expand_value);
			else
				expand_value = ft_strdup("");
			free(expand_to_search);
		}
	}
	if (token->str)
	{
		tmp = ft_strjoin(token->str, expand_value);
		free(token->str);
		free(expand_value);
	}
	else
		tmp = expand_value;
	token->str = tmp;
	*line = str;
}

void	get_str_token(t_data *data, t_token *token, char **line)
{
	char	*str;
	bool	is_in_single_quote;
	bool	is_in_double_quote;

	str = *line;
	is_in_single_quote = false;
	is_in_double_quote = false;
	token->str = NULL;
	while(*str)
	{
		if (*str == '\'' && !is_in_single_quote && !is_in_double_quote)
			is_in_single_quote = true;
		else if (*str == '\"' && !is_in_single_quote && !is_in_double_quote)
			is_in_double_quote = true;
		else if (*str == '\'' && is_in_single_quote && !is_in_double_quote)
			is_in_single_quote = false;
		else if (*str == '\"' && is_in_double_quote && !is_in_single_quote)
			is_in_double_quote = false;
		else if (*str == '$' && *(str + 1) && !is_in_single_quote)
			expand(data, token, &str, is_in_double_quote);
		else if ((!is_in_double_quote && !is_in_single_quote) && (is_special_char(str) || is_space(*str)))
		{
			if (!is_space(*str) && token->str == NULL)
				token->str = get_special_char(&str);
			*line = str;
			return;
		}
		else
		{
			if (*str == '\\' && *(str + 1))
				str++;
			add_char(&token->str, *str);// checker si c'est char 0
		}
		str++;// checker si c'est char 0
	}
	*line = str;
}

t_token	*get_last_token(t_token *token_list)
{
	while (token_list  && token_list->next)
		token_list = token_list->next;
	return (token_list);
}

void	add_token(t_data *data, char **str)
{
	t_token *last_token;
	t_token *token;

	token = (t_token *)malloc(sizeof(t_token));
	if(!token)
		return;
	token->type = 0;
	get_str_token(data, token, str);
	token->prev = NULL;
	token->next = NULL;
	if (!data->begin)
		data->begin = token;
	else
	{
		last_token = get_last_token(data->begin);
		token->prev = last_token;
		last_token->next = token;
	}
}

void	create_token_lst(t_data *data, char *str)
{
	data->begin = NULL;
	while (*str)
	{
		skip_space(&str);
		add_token(data, &str);
		get_type(get_last_token(data->begin));// check arg null
	}
}

void	print_token_list(t_token *token_list)
{
	while (token_list)
	{
		printf("%s|%d\n", token_list->str, token_list->type);
		token_list = token_list->next;
	}
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

	create_token_lst(data, str);
	print_token_list(data->begin);
	//expand_token(data);
/*	token = data->begin;

	while (token)
	{
		printf("token : [%s]\n", token->str);
		token = token->next;
	}*/
	//expand_token(data);
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
