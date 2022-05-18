/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:54:20 by achane-l          #+#    #+#             */
/*   Updated: 2022/05/18 17:42:35 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_token	*get_last_token(t_token *token_list)
{
	while (token_list  && token_list->next)
		token_list = token_list->next;
	return (token_list);
}

static bool	add_token(t_data *data, char **str)
{
	t_token *last_token;
	t_token *token;

	token = (t_token *)malloc(sizeof(t_token));
	if(!token)
		return (false);
	token->type = 0;
	get_token_str(token, str);
	if (token->str == NULL)
	{
		free(token);
		return (false);
	}
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
	return (true);
}

bool	create_token_lst(t_data *data, char *str)
{
	data->begin = NULL;
	while (*str)
	{
		skip_space(&str);
		if (add_token(data, &str))
			get_type(get_last_token(data->begin));// check arg null
		else
		{
			if (*str)
				return (false);
		}
	}
	return (true);
}

void	free_token_lst(t_data *data)
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