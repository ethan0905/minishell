/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:23:19 by esafar            #+#    #+#             */
/*   Updated: 2022/02/28 17:45:18 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	add_env_line(t_env *env, t_env *new)
{
	while (env && env->next)
		env = env->next;
	new->prev = env;
	new->next = NULL;
	env->next = new;
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

char *get_syntax(char *str)
{
	int i;
	char c;
	char *dest;

	i = 0;
	c = ' ';
	dest = NULL;
	while (str[i] && str[i] != '=')
		add_char(&dest, str[i++]);
	if (str[i] == '=')
		add_char(&dest, str[i++]);
	else
	{
		free(dest);
		return (0);
	}
	while (str[i] && (str[i] != ' ' || c != ' '))
	{
		if (c == ' ' && (str[i] == '\'' || str[i] == '\"'))
		{
			c = str[(i)];
			i++;
		}
		else if (c != ' ' && str[i] == c)
		{
			c = ' ';
			i++;
		}
		else if (str[i] == '\\' && i++)
		{
			add_char(&dest, str[i]);
			i++;
		}
		else
		{
			add_char(&dest, str[i]);
			i++;
		}
	}
	return (dest);
}

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

int	env_line_already_exist(t_data *data, t_env *new)
{
	t_env *head;
	int		len;

	len = 0;
	head = data->env;
	while (new->line[len] && new->line[len] != '=')
		len++;
	while (head && ft_strncmp(head->line, new->line, len) != 0)
		head = head->next;
	if (head == NULL)
		return (0);
	if (head->prev)
		head->prev->next = new;
	else
		data->env = new;
	if (head->next)
		head->next->prev = new;
	new->prev = head->prev;
	new->next = head->next;
	free(head->line);
	free(head);
	return (1);
}

int	ft_export(t_data *data, char *str)
{
	t_env	*new;
	char *new_str;

	new_str = get_syntax(str);
	if (!new_str)
		return (-1);
	new = create_env_line(new_str);
	if (!new)
	{
		free(new_str);
		return (-1);
	}
	free(new_str);
	if (!data->env)
		data->env = new;
	else
	{
		if (env_line_already_exist(data, new) == 0)
			add_env_line(data->env, new);
		free_tab_str(&data->test, -1);
	}
	data->test = convert_lst_to_tab(data);
	return (1);
}