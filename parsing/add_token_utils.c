/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:23:19 by esafar            #+#    #+#             */
/*   Updated: 2022/03/07 15:49:42 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	add_char_and_move(t_token *token, char *str, int *j)
{
	add_char(&token->str, str[(*j)]);
	(*j)++;
}

void	reset_char(char *c, int *j)
{
	(*c) = ' ';
	(*j)++;
}
