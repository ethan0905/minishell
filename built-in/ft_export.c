/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:23:19 by esafar            #+#    #+#             */
/*   Updated: 2022/05/23 15:50:30 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	add_env_line(t_env *env, t_env *new)
{
	while (env && env->next)
		env = env->next;
	new->prev = env;
	new->next = NULL;
	env->next = new;
}

static void	get_string(char **dest, char *str)
{
	int		i;
	bool	is_in_single_quote;
	bool	is_in_double_quote;

	i = 0;
	is_in_single_quote = false;
	is_in_double_quote = false;
	while (str && str[i])
	{
		if (str[i] == '\'' && !is_in_single_quote && !is_in_double_quote)
			is_in_single_quote = true;
		else if (str[i] == '\"' && !is_in_single_quote && !is_in_double_quote)
			is_in_double_quote = true;
		else if (str[i] == '\'' && is_in_single_quote && !is_in_double_quote)
			is_in_single_quote = false;
		else if (str[i] == '\"' && is_in_double_quote && !is_in_single_quote)
			is_in_double_quote = false;
		else
			add_char(dest, str[i]);
		i++;
	}
}

char	*get_syntax(char *str)
{
	int		i;
	char	*dest;

	dest = NULL;
	i = 0;
	while (str[i] && str[i] != '=')
		add_char(&dest, str[i++]);
	if (str[i] == '=')
		add_char(&dest, str[i++]);
	else
	{
		free(dest);
		return (0);
	}
	get_string(&dest, &str[i]);
	return (dest);
}

int	env_line_already_exist(t_data *data, t_env *new)
{
	t_env	*head;
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
	char	*new_str;

	new_str = get_syntax(str);
	if (!new_str)
		return (1);
	new = create_env_line(new_str);
	if (!new)
	{
		free(new_str);
		return (1);
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
	if (!data->test)
		return (1);
	return (0);
}
