/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:11:00 by achane-l          #+#    #+#             */
/*   Updated: 2022/03/05 17:14:40 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec_files.h"

int	count_arg_in_command(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != PIPE)
	{
		if ((!token->prev && token->type > 4) || (token->prev && token->prev->type > 4 && token->type > 4))
			count++;
		// if (token->type == CMD || (token->type == ARG && token->prev && token->prev->type > 5))
		// 	count++;
		token = token->next;
	}
	return (count);
}

int	open_file(char *filename, int type)
{
	int	fd;

	if (type == INPUT)
		fd = open(filename, O_RDONLY, 0644);
	else if (type == HEREDOC)
		return(1);//HEREDOC
	else if (type == TRUNC)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		return (-2);
	if (fd < 0)
		perror(filename);
	return (fd);
}

int	get_infile(t_token *token)
{
	int		fd;

	fd = -2;
	while (token && token->type != PIPE)
	{
		if (token->type == INPUT)
		{
			if (fd >= 0)
				close(fd);
			fd = open_file(token->next->str, INPUT);
			if (fd == -1)
				return (-1);
		}
		else if (token->type == HEREDOC)
		{
			if (fd >= 0)
				close(fd);
			fd = 1;// do HEREDOC fUNC
			if (fd == -1)
				return (-1);
		}
		token = token->next;
	}
	return (fd);
}

int	get_outfile(t_token *token)
{
	int		fd;
	
	fd = -2;
	while (token && token->type != PIPE)
	{
		if (token->type == TRUNC)
		{
			if (fd >= 0)
				close(fd);
			fd = open_file(token->next->str, TRUNC);
			if (fd == -1)
				return (-1);
		}
		else if (token->type == APPEND)
		{
			if (fd >= 0)
				close(fd);
			fd = open_file(token->next->str, APPEND);
			if (fd == -1)
				return (-1);
		}
		token = token->next;
	}
	return (fd);
}

char	**get_cmd(t_token *token)
{
	char	**cmd_param;
	int		i;

	i = 0;
	cmd_param = malloc(sizeof(char *) * (count_arg_in_command(token) + 1));
	if (cmd_param == NULL)
		return (NULL);
	cmd_param[count_arg_in_command(token)] = NULL;
	while (token && token->type != PIPE)
	{
		if ((!token->prev && token->type > 4) || (token->prev && token->prev->type > 4 && token->type > 4))
			cmd_param[i++] = ft_strcopy(token->str);//strcopy la string;
		// if (token->type == CMD || (token->type == ARG && token->prev && token->prev->type > 5))
		// 	cmd_param[i++] = token->str;//strcopy;
		token = token->next;
	}
	return (cmd_param);
}
