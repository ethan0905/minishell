/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:11:00 by achane-l          #+#    #+#             */
/*   Updated: 2022/03/08 14:30:20 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec_files.h"

int	count_arg_in_command(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == CMD || (token->type == ARG && \
		token->prev && token->prev->type > 5))
			count++;
		token = token->next;
	}
	return (count);
}

char	**get_cmd(t_token *token)
{
	char	**cmd_param;
	int		i;

	i = 0;
	cmd_param = malloc(sizeof(char *) * (count_arg_in_command(token) + 1));
	if (cmd_param == NULL)
		return (NULL);
	cmd_param[count_arg_in_command(token)] = NULL;
	while (token && token->type != PIPE)
	{
		if (token->type == CMD || (token->type == ARG && \
		token->prev && token->prev->type > 5))
			cmd_param[i++] = ft_strcopy(token->str);
		token = token->next;
	}
	return (cmd_param);
}
