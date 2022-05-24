/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:10:57 by achane-l          #+#    #+#             */
/*   Updated: 2022/05/24 01:47:34 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../utils/utils.h"

bool	quoting_gest(char c, bool *is_in_single_quote, bool *is_in_double_quote)
{
	if (c == '\'' && !(*is_in_single_quote) && !(*is_in_double_quote))
	{
		(*is_in_single_quote) = true;
		return (true);
	}
	else if (c == '\"' && !(*is_in_single_quote) && !(*is_in_double_quote))
	{
		(*is_in_double_quote) = true;
		return (true);
	}
	else if (c == '\'' && (*is_in_single_quote) && !(*is_in_double_quote))
	{
		(*is_in_single_quote) = false;
		return (true);
	}
	else if (c == '\"' && (*is_in_double_quote) && !(*is_in_single_quote))
	{
		(*is_in_double_quote) = false;
		return (true);
	}
	return (false);
}

void	get_type(t_token *token)
{
	if (token->type == DOLLAR)
		return ;
	else if (ft_strcmp(token->str, "<") == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->str, "<<") == 0)
		token->type = HEREDOC;
	else if (ft_strcmp(token->str, ">") == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->str, ">>") == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->str, "|") == 0)
		token->type = PIPE;
	else if (token->prev == NULL || token->prev->type == PIPE)
		token->type = CMD;
	else
		token->type = ARG;
}

void	get_token_str(t_token *token, char **line)
{
	char	*str;
	bool	is_in_single_quote;
	bool	is_in_double_quote;

	str = *line;
	is_in_single_quote = false;
	is_in_double_quote = false;
	token->str = NULL;
	while (*str)
	{
		if (quoting_gest(*str, &is_in_single_quote, &is_in_double_quote))
			;
		else if ((!is_in_double_quote && !is_in_single_quote) && \
		(is_special_char(str) || is_space(*str)))
		{
			if (!is_space(*str) && token->str == NULL)
				token->str = get_special_char(&str);
			break ;
		}
		else
			add_char(&token->str, *str);
		str++;
	}
	*line = str;
}
