/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:07:13 by achane-l          #+#    #+#             */
/*   Updated: 2022/05/23 18:10:23 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_files.h"

static void	read_in_stdin(t_data *data, int fd, char *word)
{
	char	*buf;
	char	*tmp;

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
}

int	here_doc(t_data *data, char *word)
{
	int		fd;

	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	read_in_stdin(data, fd, word);
	fd = open(".heredoc_tmp", O_RDONLY);
	if (fd < 0)
		unlink(".heredoc_tmp");
	return (fd);
}

void	print_error_command(char *cmd_name, int error_type)
{
	if (error_type == 1)
	{
		write (1, cmd_name, ft_strlen(cmd_name));
		write (1, ": command not executable\n", 25);
	}
	else if (error_type == 2)
	{
		write (1, cmd_name, ft_strlen(cmd_name));
		write (1, ": command not found\n", 20);
	}
}

static bool	not_special_builtin(t_data *data, t_cmd *cmd)
{
	if (ft_strcmp("echo", cmd->cmd_param[0]) == 0)
	{
		data->exit_code = ft_echo(cmd->cmd_param);
		return (true);
	}
	else if (ft_strcmp("pwd", cmd->cmd_param[0]) == 0)
	{
		data->exit_code = ft_pwd();
		return (true);
	}
	else if (ft_strcmp("cd", cmd->cmd_param[0]) == 0)
	{
		data->exit_code = ft_cd(data, cmd->cmd_param);
		return (true);
	}
	else if (ft_strcmp("env", cmd->cmd_param[0]) == 0)
	{
		data->exit_code = ft_env(data->test);
		return (true);
	}
	return (false);
}

void	select_and_exec(int save_stdout, t_data *data, t_cmd *cmd)
{
	int	i;

	if (not_special_builtin(data, cmd))
		;
	else if (ft_strcmp("export", cmd->cmd_param[0]) == 0)
	{
		i = 0;
		while (cmd->cmd_param[++i])
			data->exit_code = ft_export(data, cmd->cmd_param[i]);
	}
	else if (ft_strcmp("unset", cmd->cmd_param[0]) == 0)
	{
		i = 0;
		while (cmd->cmd_param[++i])
			data->exit_code = ft_unset(data, cmd->cmd_param[i]);
	}
	else if (ft_strcmp("exit", cmd->cmd_param[0]) == 0)
	{
		if (cmd->outfile >= 0)
		{
			dup2(save_stdout, 1);
			close(save_stdout);
		}
		ft_exit(data, cmd);
	}
}
