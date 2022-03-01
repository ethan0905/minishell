/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:11:00 by achane-l          #+#    #+#             */
/*   Updated: 2022/02/28 17:52:36 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec_files.h"

int	count_cmd(t_token *token)
{
	int count;

	count = 1;
	while (token)
	{
		if (token->type == PIPE)
			count++;
		token = token->next;
	}
	return (count);
}

int	count_type(t_token *token, int type)
{
	int count;

	count = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == type)
			count++;
		token = token->next;
	}
	return (count);
}

int	count_arg_in_command(t_token *token)
{
	int	count;

	while (token && token->type != PIPE)
	{
		if ((!token->prev && token->type > 4) || (token->prev && token->prev->type > 4 && token->type > 4))
			count++;
		token = token->next;
	}
	return (count);
}

int	*get_infile(t_token *token)
{
	int	*infile;
	int	i;
	
	infile = malloc(sizeof(int) * (count_type(token, INFILE) + count_type(token, HEREDOC)));
	if (infile == NULL)
		return (NULL);
	i = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == INFILE)
			infile[i++] = open_file(token->next->str);
		else if (token->type == HEREDOC)
			infile[i++] = -1;//return (heredoc(token->next->str)))
		token = token->next;
	}
	return (infile);
}

int	*get_outfile(t_token *token)
{
	int	*outfile;
	int	i;
	
	outfile = malloc(sizeof(int) * (count_type(token, OUTFILE) + count_type(token, A_OUTFILE)));
	if (outfile == NULL)
		return (NULL);
	i = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == OUTFILE)
			outfile[i++] = open_file(token->next->str);
		else if (token->type == A_OUTFILE)
			outfile[i++] = open_file(token->next->str);//return (heredoc(token->next->str)))
		token = token->next;
	}
	return (outfile);
}

char	**get_cmd(t_token *token)
{
	char	**cmd_param;
	int		i;

	cmd_param = malloc(sizeof(char *) * count_arg_in_command(token));
	i = 0;
	if (cmd_param == NULL)
		return (NULL);
	while (token && token->type != PIPE)
	{
		if ((!token->prev && token->type > 4) || (token->prev && token->prev->type > 4 && token->type > 4))
			cmd_param[i++] = token->str;//strcopy la string;
		token = token->next;
	}
	return (cmd_param);
}

t_cmd	*create_cmd(t_token *token, int *fds)
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->fd = fds;
	cmd->infile = get_infile(token);
	cmd->outfile = get_outfile(token);
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

void	free_cmd(t_cmd **cmds)
{
	t_cmd *cmd;

	cmd = *cmds;
	while (*cmds)
	{
		cmd = *cmds;
		*cmds = (*cmds)->next;
		close_files((*cmds)->infile);
		close_files((*cmds)->outfile);
		free((*cmds)->infile);
		free((*cmds)->outfile);
		free_tab_str((*cmds)->cmd_param, -1);
		(*cmds) = (*cmds)->next;
	}
}

void	close_files(int *files)
{
	int i;

	i = 0;
	while (files[i])
	{
		if (files[i] >= 0)
			close(files[i]);
		i++;
	}
}

t_cmd	*init_cmds(t_token *token, int *fds)
{
	t_cmd	*lst_cmd;
	t_cmd	*new_cmd;
	int 	nb_of_cmd;

	lst_cmd = NULL;
	while (token)
	{
		if (!token->prev || token->prev->type == PIPE)
		{
			new_cmd = create_cmd(token, fds);
			if (!new_cmd)
			{
				free_cmd(new_cmd);
				free_cmd(lst_cmd);
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
