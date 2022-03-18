/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:42:20 by achane-l          #+#    #+#             */
/*   Updated: 2022/03/18 15:28:54 by achane-l         ###   ########.fr       */
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

static void	update_oldpwd(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (-1);
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (!oldpwd)
		return (-1);
	ft_export(env, oldpwd);
	free(oldpwd);
}

static char *get_env_path(t_env *env, char *find)
{
	char	*path;
	while (env)
	{
		if (check_env_val(env->line, find) == 1)
		{
			path = ft_strdup(&(env->line + ft_strlen(find)));
			return (path);
		}
		env = env->next;
	}
	return (NULL);
}

static int	go_to_path(int option, t_env *env)
{
	char *path;
	int	ret;

	if (option == 0)
	{
		update_oldpwd(env);
		path = get_env_path(env, "HOME=");
		if (!path)
		{
			return(-1); //"NOT SET HOME"
		}
		
	}
	else if (option == 1)
	{
		update_oldpwd(env);
		path = get_env_path(env, "OLDPWD=");
		if (!path)
		{
			return(-1); //"NOT SET OLDPWD"
		}
	}
	ret = chdir(path);
	free(path);
	return (ret);
}

int	ft_cd(char **params, t_env *env)
{
	int ret;

	if (count_nb_arg(params) <= 2)
	{
		if (params[1])
			return (go_to_path(0, env));
		else if (ft_strcmp(params[1], "-") == 0)
			return (go_to_path(1, env));
		else
		{
			update_oldpwd(env);
			ret = chdir(params[1]);
			if (ret < 0)
				ret *= -1;
		}
		return (ret);
	}
	else
		return (1);
}