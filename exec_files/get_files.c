/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:17:54 by achane-l          #+#    #+#             */
/*   Updated: 2022/05/17 19:11:08 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec_files.h"

int	here_doc(t_data *data,char *word)
{
	char	*buf;
	char	*tmp;
	int		fd;

	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	while (1)
	{
		tmp = NULL;
		write(1, "> ", 2);
		if (get_next_line(0, &buf) < 0)
			exit(0);
		if (!ft_strncmp(word, buf, ft_strlen(word) + 1))
			break ;
		tmp = expand_str(data, buf);
		write(fd, tmp, ft_strlen(tmp));
		write(fd, "\n", 1);
		free(buf);
		free(tmp);
	}
	free(buf);
	close(fd);
	fd = open(".heredoc_tmp", O_RDONLY);
	if (fd < 0)
		unlink(".heredoc_tmp");
	return (fd);
}

int	open_file(t_data *data, char *filename, int type)
{
	int	fd;

	if (type == INPUT)
		fd = open(filename, O_RDONLY, 0644);
	else if (type == HEREDOC)
		fd = here_doc(data, filename);
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

int	get_infile(t_data *data, t_token *token)
{
	int		fd;

	fd = -2;
	while (token && token->type != PIPE)
	{
		if (token->type == INPUT)
		{
			if (fd >= 0)
				close(fd);
			fd = open_file(data, token->next->str, INPUT);
			if (fd == -1)
				return (-1);
		}
		else if (token->type == HEREDOC)
		{
			if (fd >= 0)
				close(fd);
			fd = open_file(data, token->next->str, HEREDOC);
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
			fd = open_file(NULL, token->next->str, TRUNC);
			if (fd == -1)
				return (-1);
		}
		else if (token->type == APPEND)
		{
			if (fd >= 0)
				close(fd);
			fd = open_file(NULL,token->next->str, APPEND);
			if (fd == -1)
				return (-1);
		}
		token = token->next;
	}
	return (fd);
}

void	add_file_to_cmd(t_data *data, t_cmd *cmd, t_token *token)
{
	cmd->skip_cmd = false;
	cmd->infile = get_infile(data, token);
	if (cmd->infile == -1)
	{
		cmd->skip_cmd = true;
		cmd->outfile = -1;
	}
	else
	{
		cmd->outfile = get_outfile(token);
		if (cmd->outfile == -1)
		{
			if (cmd->infile >= 0)
				close(cmd->infile);
			cmd->skip_cmd = true;
			cmd->infile = -1;
		}
	}	
}
