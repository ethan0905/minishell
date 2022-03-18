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

t_env	*add_env_line(char *line)
{
	t_env *env;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->line = ft_strdup(line);
	return (env);
}

t_env *create_env(char **env)
{
	int i = 0;
	t_env *prev;
	t_env *next;

	prev = NULL;
	next = NULL;
	while (env[i])
	{
		next = add_env_line(env[i]);
		next->prev = prev;
		if (prev)
			prev->next = next;
		prev = next;
		i++;
	}
	if (next)
		next->next = NULL;
	while (next && next->prev)
		next = next->prev;
	return (next);
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
	int i = 0;

	dest = NULL;
	lst = data->env;
	dest = (char **)malloc(sizeof(char *) * (ft_lstlen(lst) + 1));
	while (lst)
	{
		dest[i] = ft_strdup(lst->line);
		lst = lst->next;
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
//	free(tab);
}

int	ft_export(t_data *data, char *str)
{
	t_env *head;
	char *new;

	printf("ACTION = [EXPORT -> %s]\n", str);
	head = data->env;
	while (data->env && data->env->next != NULL)
		data->env = data->env->next;
	new = get_syntax(str);	
//	if (env)
//		env->next = NULL;
	if (data->env->next == NULL)
	{
		data->env->next = add_env_line(new);
//		env->next->prev = env;
	}
	data->env = head;
	data->test = convert_lst_to_tab(data);
//	free_tab(data->test);
	return (1);
}
