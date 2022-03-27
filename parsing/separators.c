/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:23:19 by esafar            #+#    #+#             */
/*   Updated: 2022/03/07 15:49:42 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
