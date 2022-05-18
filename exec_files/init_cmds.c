/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 19:13:18 by achane-l          #+#    #+#             */
/*   Updated: 2022/05/17 19:02:23 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec_files.h"

t_cmd	*create_cmd(t_data *data, t_token *token)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	add_file_to_cmd(data, cmd, token);
	cmd->cmd_param = get_cmd(token);
	cmd->next = NULL;
	return (cmd);
}

void	add_cmd(t_cmd *lst_cmd, t_cmd *new_cmd)
{
	while (lst_cmd && lst_cmd->next != NULL)
		lst_cmd = lst_cmd->next;
	lst_cmd->next = new_cmd;
}

t_cmd	*init_cmds(t_data *data,t_token *token)
{
	t_cmd	*lst_cmd;
	t_cmd	*new_cmd;

	lst_cmd = NULL;
	while (token)
	{
		if (!token->prev || token->prev->type == PIPE)
		{
			new_cmd = create_cmd(data, token);
			if (!new_cmd)
			{
				free_cmd(&new_cmd);
				free_cmd(&lst_cmd);
				return (NULL);
			}
			if (!lst_cmd)
				lst_cmd = new_cmd;
			else
				add_cmd(lst_cmd, new_cmd);
		}
		token = token->next;
	}
	return (lst_cmd);
}

void	free_cmd(t_cmd **cmds)
{
	t_cmd	*cmd;

	while (*cmds)
	{
		cmd = *cmds;
		free_tab_str(&cmd->cmd_param, -1);
		(*cmds) = (*cmds)->next;
		free(cmd);
	}
}
