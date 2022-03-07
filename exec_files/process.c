/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:35:53 by achane-l          #+#    #+#             */
/*   Updated: 2022/03/07 15:35:49 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec_files.h"

void	child_process(t_cmd *cmds, t_cmd *first, int *fd, char **env)
{
	char	**paths;

	paths = init_paths(env);
	if (paths == NULL)
		return ;
	if (check_path_cmd(cmds, paths) == 1)
	{
		close(fd[0]);
		if (cmds->infile >= 0)
		{
			dup2(cmds->infile, 0);
			close(cmds->infile);
		}
		if (cmds->outfile >= 0)
		{
			dup2(cmds->outfile, 1);
			close(cmds->outfile);
		}
		else if (cmds->next != NULL)
			dup2(fd[1], 1);
		close(fd[1]);
		execve(cmds->cmd_param[0], cmds->cmd_param, env);
	}
	write(1, "command not found\n", 19);
	if (cmds->infile >= 0)
		close(cmds->infile);
	if (cmds->outfile >= 0)
		close(cmds->outfile);
	close(fd[0]);
	close(fd[1]);
	free_cmd(&first);
	free_tab_str(&paths, -1);
	exit(-1);
}

void	parent_process(t_cmd *cmds, int *fd)
{
	close(fd[1]);
	if (cmds->infile >= 0)
		close(cmds->infile);
	if (cmds->infile == -2)
		cmds->infile = fd[0];
	if (cmds->next && cmds->next->infile == -2)
		cmds->next->infile = fd[0];
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
