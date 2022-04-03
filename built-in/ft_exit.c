/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 01:29:32 by achane-l          #+#    #+#             */
/*   Updated: 2022/04/02 02:06:24 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./built-in.h"

void	ft_exit(t_data *data, struct s_cmd *cmd)
{
	//check code exit et arg
	struct s_cmd *current;

	current = data->cmd;
	while (current)
	{
		if (cmd->infile >= 0)
			close(cmd->infile);
		if (cmd->outfile >= 0)
			close(cmd->outfile);
		current = current->next;
	}
	printf("exit\n");
	if (data->begin)
		free_lst(data);
	if (data->env)
		free_env(data->env);
	if (data->test)
		free_tab_str(&data->test, -1);
	if (data->cmd)
		free_cmd(&data->cmd);
	exit(0);
}