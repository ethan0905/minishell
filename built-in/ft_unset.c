/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:23:19 by esafar            #+#    #+#             */
/*   Updated: 2022/02/28 17:45:18 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	look_for_word(t_data *data, char *str, int lenght)
{
	int index;
	t_env *env;

	index = 0;
	env = data->env;
	while (env && env->next)
	{
		if (ft_strncmp(env->line, str, lenght) == 0)
			break ;
		env = env->next;
		index++;
	}
	return (index);
}

void	reach_good_node(t_data *data, int index)
{
	t_env *env;
	t_env *node_to_unset;

	env = data->env;
	node_to_unset = NULL;
	while (env && env->next != NULL && index > 1)
	{
		env = env->next;
		index--;
	}
	if (index == 0)
	{
		node_to_unset = data->env;
		data->env = data->env->next;
		free(node_to_unset->line);
		free(node_to_unset);
	}
	else if (index == 1)
	{
		if (env->next)
		{
			node_to_unset = env->next;
			env->next = NULL;
			free(node_to_unset->line);
			free(node_to_unset);
		}
	}
	else
	{
		node_to_unset = env->next;
		env->next = env->next->next;
		free(node_to_unset->line);
		free(node_to_unset);
	}
}

int	ft_unset(t_data *data, char *str)
{
	int index;

	index = 0;
	index = look_for_word(data, str, ft_strlen(str));
	reach_good_node(data, index);
	return (0);
}
