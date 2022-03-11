/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:06:12 by achane-l          #+#    #+#             */
/*   Updated: 2022/03/07 15:36:10 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec_files.h"

int	exec(t_data *data)
{
	t_cmd	*cmds;
	int		fd[2];
//	int		pid;

	cmds = data->cmd;
	while (cmds)
	{
		if (cmds->skip_cmd)
			cmds = cmds->next;
		else
		{
			if (pipe(fd) == -1)
				return (-1);
			pid = fork();
			if (pid < 0)
				return (-1);
			else if (pid == 0)
				child_process(cmds, data->cmd, fd, data->envp);
			else
				parent_process(cmds, fd);
			cmds = cmds->next;
		}
	}
	wait_all_and_finish(data->cmd);
	free_cmd(&data->cmd);
	return (1);
}

// int main (int argc, char **argv, char **env)
// {
// 	t_token *lst;
// 	t_data test;
// 	t_cmd	*cmd;
// 	(void)argc;

// 	lst = create_token_lst(argv[1]);
// 	test.begin = lst;
// 	cmd = init_cmds(lst); 
// 	free_lst(&test);
// 	exec(cmd, env);
// }
