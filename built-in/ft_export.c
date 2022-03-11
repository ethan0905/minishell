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

int	ft_export(t_data *data, char *str)
{
	t_env *env;

	data->env = create_env(data->envp);
	env = data->env;
	while (env && env->next != NULL)
		env = env->next;
	str = get_syntax(str);	
//	if (env)
//		env->next = NULL;
	if (env->next == NULL)
	{
		env->next = add_env_line(str);
		env->next->prev = env;
	}
	//juste poru le test
	while (data->env)
	{	
		printf("L++ >>> %s\n", data->env->line);
		data->env = data->env->next;
	}
	return (1);
}
