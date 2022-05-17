/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:23:19 by esafar            #+#    #+#             */
/*   Updated: 2022/05/17 17:16:53 by achane-l         ###   ########.fr       */
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

int	get_len_of_env_var(char *env)
{
	int i;

	i = 0;
	while(env[i] && env[i] != '=')
		i++;
	return (i);
}

char	*my_getenv(t_data *data, char *expand_to_search)
{
	int	i;
	int expand_len;

	i = 0;
	expand_len = ft_strlen(expand_to_search);
	while (data->test[i])
	{
		if (ft_strncmp(expand_to_search, data->test[i], expand_len) == 0 && get_len_of_env_var(data->test[i]) == expand_len)
			return (ft_strdup(data->test[i] + ft_strlen(expand_to_search) + 1));
		i++;
	}
	return (NULL);
}

void	expand(t_data *data, t_token *token, char **line, bool is_in_double_quote)
{
	char *expand_to_search;
	char	*expand_value;
	char	*str;
	char	*tmp;

	str = *line;
	//expand_to_search = ft_strdup("");
	expand_to_search = NULL;
	expand_value = NULL;
	tmp = NULL;
	str++;
	if (*str == '\'' || (*str == '\"' && !is_in_double_quote))// and is not in double quote
	{
		*line = str;
		return ;
	}
	if (*str == '?')
	{
		expand_value = ft_itoa(data->exit_code);
		str++;
	}
	else if (*str == '$')
	{
		expand_value = ft_itoa(data->signal.pid);
		str++;
	}
	else
	{
		//expand_to_search = ft_strdup("");
		if (is_in_double_quote)
		{
			while (*str != '\"' && (!is_special_char(str) && !is_space(*str)))
			{
				add_char(&expand_to_search, *str);
				str++;
			}
			printf("suiote |%s|\n", str);
		}
		else
		{
			puts("PASSER");
			while (*str && (*str != '\'' && *str != '\"' && *str != '$') && (!is_special_char(str) && !is_space(*str)))
			{
				add_char(&expand_to_search, *str);
				str++;
			}
		}
		if (expand_to_search)
		{
			printf("expand |%s|\n", expand_to_search);
			expand_value = my_getenv(data, expand_to_search);
			if (expand_value)
				expand_value = ft_strdup(expand_value);
			else
				expand_value = ft_strdup("");
			free(expand_to_search);
		}
		else
			expand_value = ft_strdup("$");// avoir le else
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
	bool	expand_launch;

	str = *line;
	is_in_single_quote = false;
	is_in_double_quote = false;
	token->str = NULL;
	while(*str)
	{
		expand_launch = false;
		if (*str == '\'' && !is_in_single_quote && !is_in_double_quote)
			is_in_single_quote = true;
		else if (*str == '\"' && !is_in_single_quote && !is_in_double_quote)
			is_in_double_quote = true;
		else if (*str == '\'' && is_in_single_quote && !is_in_double_quote)
			is_in_single_quote = false;
		else if (*str == '\"' && is_in_double_quote && !is_in_single_quote)
			is_in_double_quote = false;
		else if (*str == '$' && *(str + 1) && !is_in_single_quote)
		{
			expand(data, token, &str, is_in_double_quote);
			expand_launch = true;
		}
		else if ((!is_in_double_quote && !is_in_single_quote) && (is_special_char(str) || is_space(*str)))
		{
			if (!is_space(*str) && token->str == NULL)
				token->str = get_special_char(&str);
			*line = str;
			return;
		}
		else
		{
			if (*str == '\\' && *(str + 1))//A voir pour enlever backslash
				str++;
			add_char(&token->str, *str);// checker si c'est char 0
		}
		if (!expand_launch)
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

char *expand_result(t_data *data,char **line, bool is_in_double_quote)
{
	char *expand_to_search;
	char	*expand_value;
	char	*str;

	str = *line;
	expand_to_search = NULL;
	expand_value = NULL;
	str++;
	if (*str == '\'' || (*str == '\"' && !is_in_double_quote))// and is not in double quote
	{
		*line = str;
		return ("");
	}
	if (*str == '?')
	{
		expand_value = ft_itoa(data->exit_code);
		str++;
	}
	else if (*str == '$')
	{
		expand_value = ft_itoa(data->signal.pid);
		str++;
	}
	else
	{
		if (is_in_double_quote)
		{
			while (*str != '\"' && (!is_special_char(str) && !is_space(*str)))
			{
				add_char(&expand_to_search, *str);
				str++;
			}
		}
		else
		{
			while (*str && (*str != '\'' && *str != '\"' && *str != '$') && (!is_special_char(str) && !is_space(*str)))
			{
				add_char(&expand_to_search, *str);
				str++;
			}
		}
		if (expand_to_search)
		{
			expand_value = my_getenv(data, expand_to_search);
			if (expand_value)
				expand_value = ft_strdup(expand_value);
			else
				expand_value = ft_strdup("");
			free(expand_to_search);
		}
		else
			expand_value = ft_strdup("$");// avoir le else
	}
	*line = str;
	return (expand_value);
}

char *expand_str(t_data *data, char *str)
{
	char	*final_str;
	bool is_in_single_quote;
	bool is_in_double_quote;
	bool expand_exec;

	is_in_single_quote = false;
	is_in_double_quote = false;
	final_str = ft_strdup("");
	while (*str)
	{
		expand_exec = false;
		if (*str == '\'' && !is_in_single_quote && !is_in_double_quote)
			is_in_single_quote = true;
		else if (*str == '\"' && !is_in_single_quote && !is_in_double_quote)
			is_in_double_quote = true;
		else if (*str == '\'' && is_in_single_quote && !is_in_double_quote)
			is_in_single_quote = false;
		else if (*str == '\"' && is_in_double_quote && !is_in_single_quote)
			is_in_double_quote = false;
		if (*str == '$' && ((*str + 1) && ((*str + 1) != '\'' && (*str + 1) != '\"'))&& !is_in_single_quote){
			expand_exec = true;
			final_str = ft_strjoin(final_str, expand_result(data, &str, is_in_double_quote));
		}
		else
			add_char(&final_str, *str);
		if (!expand_exec)
			str++;
	}
	return final_str;
}

int	parse(t_data *data, char *str)
{
//	t_token *token;
	char *str_parse;

	if (ft_strlen(str) == 0)
		return (0);
	if (!check_unclosed_quote(str))
	{
		printf("Error: unclosed quote.\n");
		fflush(stdout);
		return (0);
	}
	str_parse = str;
	str_parse = expand_str(data, str_parse);
	create_token_lst(data, str_parse);
	// print_token_list(data->begin);
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
