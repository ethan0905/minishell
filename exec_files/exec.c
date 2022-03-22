/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:06:12 by achane-l          #+#    #+#             */
/*   Updated: 2022/03/22 15:39:14 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec_files.h"

int	exec(t_data *data)
{
	t_cmd	*cmds;
	int		fd[2];

	cmds = data->cmd;
	while (cmds)
	{
		if (cmds->skip_cmd)
			cmds = cmds->next;
		else
		{
			if (pipe(fd) == -1)
				return (-1);
			data->signal.pid = fork();
			if (data->signal.pid < 0)
				return (-1);
			else if (data->signal.pid == 0)
				child_process(data, cmds, fd);
			else
				parent_process(cmds, fd);
			cmds = cmds->next;
		}
	}
	wait_all_and_finish(data->cmd);
	free_cmd(&data->cmd);
	free_lst(data);
	return (1);
}
