/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:23:19 by esafar            #+#    #+#             */
/*   Updated: 2022/04/07 18:28:41 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_space(char c)
{
	if (c && (c == ' ' || c == '\n' || c == '\r' || c == '\f' || c == '\t' || c == '\v'))
		return (true);
	return (false);
}

void	skip_space(char **line)
{
	char *str;

	str = *line;
	while (is_space(*str))
		str++;
	*line = str;
}

int	ignore_separator(char *str)
{

	if (*str && *str == '\\' && *(str + 1) && *(str + 1) == '|')
		return (1);
	else if (*str && *str == '\\' && *(str + 1) && *(str + 1) == '>')
	{
		if (*(str + 2) && *(str + 2) == '>')
			return (1);
	}
	else if (*str && *str == '\\' && *(str + 1) && *(str + 1) == '>' && *(str + 2) && *(str + 2) == '>')
		return (1);
	else if (*str && *str == '\\' && *(str + 1) && *(str + 1) == ';')
		return (1);
	else if (*str && *str == '\\' && *(str + 1) && *(str + 1) == '$')
		return (1);
	return (0);
}
