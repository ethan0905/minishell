/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:27:08 by achane-l          #+#    #+#             */
/*   Updated: 2022/05/18 15:36:13 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstlen(t_env *lst)
{
	int count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return(count);
}

char **convert_lst_to_tab(t_data *data)
{
	t_env *lst;
	char **dest;
	int i;

	dest = NULL;
	i = 0;
	lst = data->env;
	dest = (char **)malloc(sizeof(char *) * (ft_lstlen(lst) + 1));
	if (!dest)
		return (NULL);
	while (lst)
	{
		dest[i] = ft_strdup(lst->line);
		lst = lst->next;
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

t_env	*create_env_line(char *line)
{
	t_env *env;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->line = ft_strdup(line);
	env->prev = NULL;
	env->next = NULL;
	return (env);
}

t_env	*create_env(char **env)
{
	t_env	*head;
	t_env	*new;

	head = NULL;
	while (*env)
	{
		if (!head)
		{
			new = create_env_line(*env);
			if (!new)
				return (NULL);
			head = new;
		}
		else
		{
			new = create_env_line(*env);
			if (!new)
			{
				free_env(head);
				return (NULL);
			}
			add_env_line(head, new);
		}
		env++;
	}
	return (head);
}

void	free_env(t_env *env)
{
	t_env	*current;

	while (env)
	{
		current = env;
		env = env->next;
		free(current->line);
		free(current);
	}
}