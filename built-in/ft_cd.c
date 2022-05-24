/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:42:20 by achane-l          #+#    #+#             */
/*   Updated: 2022/05/24 01:23:32 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtin.h"

static int	count_nb_arg(char **params)
{
	int	count;

	count = 0;
	while (params[count])
		count++;
	return (count);
}

static void	update_oldpwd(t_data *data, char *param)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		perror(param);
		return ;
	}
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (!oldpwd)
		return ;
	ft_export(data, oldpwd);
	free(oldpwd);
}

int	ft_cd(t_data *data, char **params)
{
	int	ret;

	if (count_nb_arg(params) <= 2)
	{
		if (params[1] == NULL)
			return (1);
		update_oldpwd(data, params[1]);
		ret = chdir(params[1]);
		if (ret < 0)
			ret *= -1;
		if (ret == 1)
		{
			write(1, params[1], ft_strlen(params[1]));
			write(1, " : Aucun fichier ou dossier de ce type\n", 39);
		}
		return (ret);
	}
	return (1);
}
