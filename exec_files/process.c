/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:35:53 by achane-l          #+#    #+#             */
/*   Updated: 2022/03/15 11:22:11 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec_files.h"

void	child_process(t_data *data, t_cmd *cmd, int *fd)
{
	char	**paths;

	paths = init_paths(data->env);
	if (paths == NULL)
		return ;
	if (check_path_cmd(cmd, paths) == 1)
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
		execve(cmd->cmd_param[0], cmd->cmd_param, data->env);
	}
	if (!cmd->cmd_param[0])
		exit(-1);
	execve(cmd->cmd_param[0], cmd->cmd_param, data->env);
	write(1, "command not found\n", 19);
	perror(cmd->cmd_param[0]);
	if (cmd->infile >= 0)
		close(cmd->infile);
	if (cmd->outfile >= 0)
		close(cmd->outfile);
	close(fd[0]);
	close(fd[1]);
	free_cmd(&cmd);
	free_tab_str(&paths, -1);
	exit(-1);
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
