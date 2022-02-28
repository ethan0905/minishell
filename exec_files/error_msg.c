/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 13:00:51 by achane-l          #+#    #+#             */
/*   Updated: 2022/02/21 14:00:19 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_files.h"

static void	puterr(char *mes_err, char *err_val)
{
	write(1, mes_err, ft_strlen(mes_err));
	write(1, err_val, ft_strlen(err_val));
	write(1, "\n", 1);
}

void	error_management(char *arg, int error)
{
	if (error == 1)
		puterr("pipex: no such file or directory: ", arg);
	else if (error == 2)
		puterr("pipex: permission denied: ", arg);
	else if (error == 3)
		puterr("pipex: command not found: ", arg);
}