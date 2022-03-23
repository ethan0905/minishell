/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:06:12 by achane-l          #+#    #+#             */
/*   Updated: 2022/03/23 16:08:55 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec_files.h"

bool	is_built_in(char *cmd)
{
	if (ft_strcmp("echo", cmd) == 0 || ft_strcmp("env", cmd) == 0 \
	|| ft_strcmp("export", cmd) == 0 || ft_strcmp("pwd", cmd) == 0 \
	|| ft_strcmp("exit", cmd) == 0 || ft_strcmp("cd", cmd) == 0)
		return (true);
	return (false);
}

bool	command_exist(t_data *data, t_cmd *cmd)
{
	char	**paths;

	paths = init_paths(data->env);
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

int	launch_built_in(t_cmd *cmd)
{
	int	ret;
	int	save_stdout;

	ret = 0;
	if (cmd->outfile >= 0)
	{
		save_stdout = dup(1);
		dup2(cmd->outfile, 1);
	}
	if (ft_strcmp("echo", cmd->cmd_param[0]) == 0)
		ret = ft_echo(cmd->cmd_param);
	else if (ft_strcmp("pwd", cmd->cmd_param[0]) == 0)
		ret = ft_pwd();
	if (cmd->outfile >= 0)
	{
		dup2(save_stdout, 1);
		close(save_stdout);
	}
	return (ret);
}

void	launch_cmd(t_data *data, t_cmd *cmd, int *fd)
{
	data->signal.pid = fork();
	if (data->signal.pid < 0)
		return ;
	else if (data->signal.pid == 0)
		child_process(data, cmd, fd);
	else
		parent_process(cmd, fd);
}

int	exec(t_data *data)
{
	t_cmd	*cmds;
	int		fd[2];

	cmds = data->cmd;
	if (cmds && cmds->skip_cmd == false && !cmds->next \
	&& is_built_in(cmds->cmd_param[0]))
		data->exit_code = launch_built_in(cmds);
	else
	{
		while (cmds)
		{
			if (cmds->skip_cmd)
				cmds = cmds->next;
			else
			{
				if (pipe(fd) == -1)
					return (-1);
				launch_cmd(data, cmds, fd);
				cmds = cmds->next;
			}
		}
	}
	wait_all_and_finish(data->cmd);
	free_cmd(&data->cmd);
	return (1);
}
