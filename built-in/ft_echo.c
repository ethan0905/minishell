/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:56:15 by achane-l          #+#    #+#             */
/*   Updated: 2022/04/03 16:36:39 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./built-in.h"

int	ft_echo(char **args)
{
	int	count_args;
	int i;
	bool	nl;

	count_args = 0;
	i = 1;
	nl = true;
	while(args[count_args])
		count_args++;
	while(i < count_args)
	{
		if (i == 1 && args[i] && ft_strcmp(args[i], "-n") == 0)
		{
			i++;
			nl = false;
		}
		write(1, args[i], ft_strlen(args[i]));
		if (i != count_args - 1)
			write(1, " ", 1);
		i++;
	}
	if (nl)
		write(1, "\n", 1);
	return (0);
}
