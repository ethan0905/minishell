/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 13:28:29 by achane-l          #+#    #+#             */
/*   Updated: 2022/02/28 15:22:21 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec_files.h"

int	check_env_val(char *src, char *find)
{
	int	i;

	i = 0;
	while (src && src[i] && find && find[i])
	{
		if (src[i] == find[i])
			i++;
		else
			break ;
	}
	if (find[i] == 0)
		return (1);
	return (0);
}

char	**init_paths(char **env)
{
	char	**paths;
	int		i;

	i = 0;
	while (env[i])
	{
		if (check_env_val(env[i], "PATH=") == 1)
			break ;
		i++;
	}
	paths = ft_split(env[i] + 5, ':');
	return (paths);
}

int	check_path_cmd(t_cmd *my_cmd, char **paths)
{
	int		i;
	char	*path_cmd;
	char	*end_path;

	if (access(my_cmd->cmd_param[0], X_OK) == 0)
		return (1);
	i = 0;
	end_path = ft_strjoin("/", my_cmd->cmd_param[0]);
	while (paths[i])
	{
		path_cmd = ft_strjoin(paths[i], end_path);
		if (access(path_cmd, X_OK) == 0)
		{
			free(end_path);
			free(my_cmd->cmd_param[0]);
			my_cmd->cmd_param[0] = path_cmd;
			return (1);
		}
		free(path_cmd);
		i++;
	}
	free(end_path);
	return (0);
}
