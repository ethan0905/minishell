/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:23:19 by esafar            #+#    #+#             */
/*   Updated: 2022/02/28 17:45:18 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_str_before_dollar(t_token *token, t_expand *expand, int i)
{
	int j;

	//1 : je recup ce qui est avant mon $ dans line
	j = 0;
	while (j < i && token->str[j])
	{
		if (token->str[j] == '\\')
		{
			expand->expand_or_not = 0;
			j++;
		}
		add_char(&expand->line, token->str[j++]);
	}
}

void	get_expand(t_data *data, t_token *token, t_expand *expand, int i)
{
	//2: je recup ce qui est apres mon $ dans dest
	if (token->str[i] && token->str[i + 1])
	{
		i++;
		while (token->str[i] && token->str[i] != '\0')
		{
			add_char(&expand->dest, token->str[i]);
			i++;
		}
	//3: je recup mon pointeur sur la bonne line dans env
		if (ft_strcmp(expand->dest, "?") == 0)
			expand->expand = ft_itoa(data->exit_code); //get exit code here
		else
			expand->expand = getenv(expand->dest);
	}
	else
		expand->expand = ft_strdup("$");
}

void	get_line(t_expand *expand)
{
	//5: j'exec
	if (expand->expand_or_not == 0)
	{	
		expand->line = ft_strjoin(expand->line, expand->dest);
	}
	else
	{
		if (!expand->line && ft_strcmp(expand->expand, "$") == 0)//doesnt look to be used
			expand->line = ft_strdup("$");
		else if (!expand->line && expand->expand)
			expand->line = ft_strdup(expand->expand);
		else if (expand->line && expand->expand)
			expand->line = ft_strjoin(expand->line, expand->expand);
	}
}

int	check_env(t_data *data, t_token *token, int i)
{
	t_expand expand;

	expand.dest = NULL;
	expand.expand = NULL;
	expand.line = NULL;
	expand.expand_or_not = 1;
	get_str_before_dollar(token, &expand, i);
	get_expand(data, token, &expand, i);
	get_line(&expand);
	free(token->str);
	if (expand.line)
		token->str = ft_strdup(expand.line);
	else
		token->str = ft_strdup("");
	return (i);
}

void	expand_token(t_data *data)
{
	t_token *token;
	int i = 0;

	token = data->begin;
	while (token)
	{
		i = 0;
		while (token->str && token->str[i])
		{
			if (token->str[i] == '$')
			{
				i = check_env(data, token, i);
			}
			i++;
		}
		token = token->next;
	}
}
