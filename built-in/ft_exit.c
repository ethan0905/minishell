/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 01:29:32 by achane-l          #+#    #+#             */
/*   Updated: 2022/04/07 02:49:31 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./built-in.h"

bool	str_is_number(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (str && (*str >= '0' && *str <= '9'))
		str++;
	return (true);
}

int	exitCode(char *str)
{
	unsigned long long	exit_code;
	int					neg;

	exit_code = 0;
	neg = 1;
	if (ft_strlen(str) > 20 || !str_is_number(str))
		return (-2);
	else
	{
		if (*str == '-' || *str == '+')
		{
			if (*str == '-')
				neg = -1;
			str++;
		}
		while (*str >= '0' && *str <= '9')
		{
			exit_code = (exit_code * 10) + (*str - '0');
			if ((neg == -1 && (exit_code - 1) > LONG_MAX) || (neg == 1 && (exit_code > LONG_MAX)))
				return (-2);
			str++;
		}
		if (*str != 0)
			return (-2);
		return ((neg * exit_code) % 256);
	}
}

void	ft_exit(t_data *data, struct s_cmd *cmd)
{
	struct s_cmd *current;

	current = data->cmd;
	while (current)
	{
		if (cmd->infile >= 0)
			close(cmd->infile);
		if (cmd->outfile >= 0)
			close(cmd->outfile);
		current = current->next;
	}
	printf("exit\n");
	if (cmd->cmd_param[1])
	{
		data->exit_code = exitCode(cmd->cmd_param[1]);
		if (data->exit_code == -2)
			data->exit_code *= -1;
		else if (cmd->cmd_param[2] && data->exit_code >= 0)
		{
			data->exit_code = 1;
			return ;
		}
	}
	if (data->begin)
		free_lst(data);
	if (data->env)
		free_env(data->env);
	if (data->test)
		free_tab_str(&data->test, -1);
	if (data->cmd)
		free_cmd(&data->cmd);
	exit(data->exit_code);
}