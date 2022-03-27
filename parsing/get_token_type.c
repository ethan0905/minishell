/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:23:19 by esafar            #+#    #+#             */
/*   Updated: 2022/03/07 15:49:42 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_type(t_token *token, int sep)
{
	if (ft_strcmp(token->str, "<") == 0 && sep == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->str, "<<") == 0 && sep == 0)
		token->type = HEREDOC;
	else if (ft_strcmp(token->str, ">") == 0 && sep == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->str, ">>") == 0 && sep == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->str, "|") == 0 && token->type != ARG && sep == 0)
		token->type = PIPE;
	else if (ft_strcmp(token->str, "$") == 0 && sep == 0)
		token->type = DOLLAR;
	else if (token->prev == NULL || token->prev->type == PIPE) //temporaire
		token->type = CMD;
	else
		token->type = ARG;
}
