/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:23:19 by esafar            #+#    #+#             */
/*   Updated: 2022/05/24 12:32:23 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

bool	is_not_a_var_name(char *str)
{
	while (str && *str)
	{
		if (*str == '=')
			return (false);
		str++;
	}
	return (true);
}

void	reach_good_node(t_data *data, char *str)
{
	t_env	*env;
	t_env	*node_to_unset;

	env = data->env;
	node_to_unset = NULL;
	if (env && ft_strncmp(env->line, str, ft_strlen(str)) == 0)
	{
		node_to_unset = data->env;
		data->env = data->env->next;
		if (data->env)
			data->env->prev = NULL;
		free(node_to_unset->line);
		free(node_to_unset);
	}
	else
	{
		while (env)
		{
			if (ft_strncmp(env->line, str, ft_strlen(str)) == 0)
			{
				node_to_unset = env;
				env->prev->next = node_to_unset->next;
				if (env->next != NULL)
					env->next->prev = node_to_unset->prev;
				free(node_to_unset->line);
				free(node_to_unset);
				break ;
			}
			env = env->next;
		}
	}
}
//a voir juste la boucle

int	ft_unset(t_data *data, char *str)
{
	if (!data->env || !is_not_a_var_name(str))
		return (1);
	reach_good_node(data, str);
	free_tab_str(&data->test, -1);
	data->test = convert_lst_to_tab(data);
	return (0);
}
