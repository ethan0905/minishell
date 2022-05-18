/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:13:06 by achane-l          #+#    #+#             */
/*   Updated: 2022/05/18 18:42:35 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../minishell.h"

static char    *get_expand_to_search(char **line)
{
    char *str;
    char *expand_to_search;

    expand_to_search = NULL;
    str = *line;
	while (*str && (*str != '\'' && *str != '\"' && *str != '$') && (!is_special_char(str) && !is_space(*str)))
	{
		add_char(&expand_to_search, *str);
		str++;
	}
    *line = str;
    return (expand_to_search);
}

static char    *get_expand_value(t_data *data, char *expand_to_search)
{
    char *expand_value;

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
    return (expand_value);
}

static char *expand_result(t_data *data,char **line, bool is_in_double_quote)
{
	char	*expand_value;
	char	*str;

	str = *line;
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
        expand_value = get_expand_value(data, get_expand_to_search(&str));
	*line = str;
	return (expand_value);
}

void	join_expand(t_data *data, char **final_str, char **str, bool is_in_double_quote)
{
	char *tmp[2];

	tmp[0] = expand_result(data, str, is_in_double_quote);
	tmp[1] = ft_strjoin(*final_str, tmp[0]);
	if (*final_str)
		free(*final_str);
	if (tmp[0])
		free(tmp[0]);
	*final_str = tmp[1];
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
		if (*str == '$' && (*(str + 1) && (*(str + 1) != '\'' && *(str + 1) != '\"')) && !is_in_single_quote){
			expand_exec = true;
			join_expand(data, &final_str, &str, is_in_double_quote);
		}
		else
			add_char(&final_str, *str);
		if (!expand_exec)
			str++;
	}
	return final_str;
}
