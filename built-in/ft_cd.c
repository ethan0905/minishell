/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:42:20 by achane-l          #+#    #+#             */
/*   Updated: 2022/04/04 19:39:50 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./built-in.h"

static int	count_nb_arg(char **params)
{
	int	count;

	count = 0;
	while (params[count])
		count++;
	return (count);
}

static void	update_oldpwd(t_data *data)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return;
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (!oldpwd)
		return;
	ft_export(data, oldpwd);
	free(oldpwd);
}

int	ft_cd(t_data *data, char **params)
{
	int ret;

	if (count_nb_arg(params) <= 2)
	{
		update_oldpwd(data);
		ret = chdir(params[1]);
		if (ret < 0)
			ret *= -1;
		return (ret);
	}
	return (1);
}
