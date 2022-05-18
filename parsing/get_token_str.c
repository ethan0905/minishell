/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:23:19 by esafar            #+#    #+#             */
/*   Updated: 2022/05/18 18:27:17 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_type(t_token *token)
{
	if (token->type == DOLLAR)
		return;
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
	else if (token->prev == NULL || token->prev->type == PIPE) //temporaire
		token->type = CMD;
	else
		token->type = ARG;
}

void	get_token_str(t_token *token, char **line)
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
		else if ((!is_in_double_quote && !is_in_single_quote) && (is_special_char(str) || is_space(*str)))
		{
			if (!is_space(*str) && token->str == NULL)
				token->str = get_special_char(&str);
			break;
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