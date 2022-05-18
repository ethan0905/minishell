/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:23:19 by esafar            #+#    #+#             */
/*   Updated: 2022/05/18 15:21:44 by achane-l         ###   ########.fr       */
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