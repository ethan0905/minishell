/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:22:27 by achane-l          #+#    #+#             */
/*   Updated: 2022/05/24 02:56:48 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec_files.h"

bool	is_built_in(char *cmd)
{
	if (!cmd)
		return (false);
	if (ft_strcmp("echo", cmd) == 0 || ft_strcmp("env", cmd) == 0 \
	|| ft_strcmp("export", cmd) == 0 || ft_strcmp("pwd", cmd) == 0 \
	|| ft_strcmp("exit", cmd) == 0 || ft_strcmp("cd", cmd) == 0 \
	|| ft_strcmp("unset", cmd) == 0)
		return (true);
	return (false);
}

bool	command_exist(t_data *data, t_cmd *cmd)
{
	char	**paths;

	paths = init_paths(data->test);
	if (paths == NULL)
		return (false);
	if (check_path_cmd(cmd, paths) == 1)
	{
		free_tab_str(&paths, -1);
		return (true);
	}
	free_tab_str(&paths, -1);
	return (false);
}

void	launch_built_in(t_data *data, t_cmd *cmd)
{
	int	save_stdout;

	save_stdout = -1;
	if (cmd->outfile >= 0)
	{
		save_stdout = dup(1);
		dup2(cmd->outfile, 1);
	}
	select_and_exec(save_stdout, data, cmd);
	if (cmd->outfile >= 0)
	{
		dup2(save_stdout, 1);
		close(save_stdout);
	}
}

void	launch_cmd(t_data *data, t_cmd *cmd, int *fd)
{
	data->signal.pid = fork();
	if (data->signal.pid < 0)
		return ;
	else if (data->signal.pid == 0)
	{
		if (cmd->cmd_param[0])
			child_process(data, cmd, fd);
		else
		{
			data->exit_code = 0;
			exit_process(data, fd);
		}
	}
	else
		parent_process(cmd, fd);
}

int	exec(t_data *data)
{
	t_cmd	*cmds;
	int		fd[2];

	cmds = data->cmd;
	if (cmds && cmds->skip_cmd == false && !cmds->next \
	&& (cmds->cmd_param[0] && is_built_in(cmds->cmd_param[0])))
		launch_built_in(data, cmds);
	else
	{
		while (cmds)
		{
			if (pipe(fd) == -1)
				return (-1);
			launch_cmd(data, cmds, fd);
			cmds = cmds->next;
		}
		wait_all_and_finish(data, data->cmd);
	}
	free_cmd(&data->cmd);
	return (1);
}
