/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:35:53 by achane-l          #+#    #+#             */
/*   Updated: 2022/04/05 16:34:43 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec_files.h"

void	exit_process(t_data *data, int *fd)
{
	t_cmd	*current;

	current = data->cmd;
	while (current)
	{
		if (current->infile >= 0)
			close(current->infile);
		if (current->outfile >= 0)
			close(current->outfile);
		current = current->next;
	}
	close(fd[0]);
	close(fd[1]);
	free_cmd(&data->cmd);
	free_lst(data);
	free_tab_str(&data->test, -1);
	free_env(data->env);
	exit(data->exit_code);
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
	if (cmd->skip_cmd)
		data->exit_code = 1;
	else if (is_built_in(cmd->cmd_param[0]))
	{
		close(fd[0]);
		if (cmd->outfile < 0 && cmd->next)
			cmd->outfile = fd[1];
		else
			close(fd[1]);
		launch_built_in(data, cmd);
	}
	else if (command_exist(data, cmd))
	{
		redirect_in_out(cmd, fd);
		execve(cmd->cmd_param[0], cmd->cmd_param, data->test);
		data->exit_code = 126;
	}
	else
	{
		write (1, cmd->cmd_param[0], ft_strlen(cmd->cmd_param[0]));
		write (1, ": command not found\n", 20);
		data->exit_code = 127;
	}
	exit_process(data, fd);
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

void	wait_all_and_finish(t_data *data, t_cmd *cmds)
{
	int	status;
	int	pid;

	while (cmds)
	{
		pid = waitpid(0, &status, 0);
		if (pid == data->signal.pid)
		{
			if (WIFEXITED(status))
				data->exit_code = WEXITSTATUS(status); //il faut l'exit code de la derniere commande
		}
		if (cmds->outfile >= 0)
			close(cmds->outfile);
		if (cmds->infile >= 0)
			close(cmds->infile);
		cmds = cmds->next;
	}
}
