/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:35:53 by achane-l          #+#    #+#             */
/*   Updated: 2022/03/23 16:08:42 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec_files.h"

void	exit_process(t_data *data, t_cmd *cmd, int *fd)
{
	if (cmd->infile >= 0)
		close(cmd->infile);
	if (cmd->outfile >= 0)
		close(cmd->outfile);
	close(fd[0]);
	close(fd[1]);
	free_cmd(&data->cmd);
	free_lst(data);
	exit(-1);
}

void	redirect_in_out(t_cmd *cmd, int *fd)
{
	close(fd[0]);
	if (cmd->infile >= 0)
	{
		dup2(cmd->infile, 0);
		close(cmd->infile);
	}
	if (cmd->outfile >= 0)
	{
		dup2(cmd->outfile, 1);
		close(cmd->outfile);
	}
	else if (cmd->next != NULL)
		dup2(fd[1], 1);
	close(fd[1]);
}

void	child_process(t_data *data, t_cmd *cmd, int *fd)
{
	if (is_built_in(cmd->cmd_param[0]))
	{
		if (cmd->outfile < 0 && cmd->next)
			cmd->outfile = fd[1];
		launch_built_in(cmd);
	}
	else if (command_exist(data, cmd))
	{
		redirect_in_out(cmd, fd);
		execve(cmd->cmd_param[0], cmd->cmd_param, data->env);
	}
	else
	{
		write (1, cmd->cmd_param[0], ft_strlen(cmd->cmd_param[0]));
		write (1, ": command not found\n", 20);
	}
	exit_process(data, cmd, fd);
}

void	parent_process(t_cmd *cmd, int *fd)
{
	close(fd[1]);
	if (cmd->infile >= 0)
		close(cmd->infile);
	if (cmd->infile == -2)
		cmd->infile = fd[0];
	if (cmd->next && cmd->next->infile == -2)
		cmd->next->infile = fd[0];
	else
		close(fd[0]);
	return ;
}

void	wait_all_and_finish(t_cmd *cmds)
{
	while (cmds)
	{
		waitpid(0, NULL, 0);
		if (cmds->outfile >= 0)
			close(cmds->outfile);
		if (cmds->infile >= 0)
			close(cmds->infile);
		cmds = cmds->next;
	}
}
