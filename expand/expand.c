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

int	check_env(t_token *token, int i)
{
	char *dest;
	char *expand;
	char *line;
	int j;
	int expand_or_not;

	dest = NULL;
	expand = NULL;
	line = NULL;
	expand_or_not = 1;
	printf("TOKEN->STR = [%s]\n", token->str);
	//1 : je recup ce qui est avant mon $ dans line
	j = 0;
	while (j < i && token->str[j])
	{
		if (token->str[j] == '\\')
		{
			expand_or_not = 0;
			j++;
		}
		add_char(&line, token->str[j++]);
	}
	printf("line equals: [%s]\n", line);
	//2: je recup ce qui est apres mon $ dans line
	i++;
	while (token->str[i] && token->str[i] != '\0')
		add_char(&dest, token->str[i++]);
	printf("DEST: %s\n", dest);

	//3: je recup mon pointeur sur la bonne line dans env
	expand = getenv(dest);
	printf("EXPAND: [%s]\n", expand);
	
	//4: check si je dois expand ma str ou non
/*	j = 0;
	while (token->str[j] && token->str[j] != '$')
		j++;
	if (j > 0 && token->str[j-1] == '\\')
		expand_or_not = 0;
	else if (j > 0 && token->str[j-1] != '\\')
		expand_or_not = 1;*/
	printf("EXPAND OR NOT? %d\n", expand_or_not);

	//5: j'exec
	if (expand_or_not == 0)
	{
		line = ft_strjoin(line, dest);
		printf("line equals: [%s]\n", line);
	}
	else
	{
		if (!line)
			line = ft_strdup(expand);
		else
			line = ft_strjoin(line, expand);
		printf("line equals: [%s]\n", line);
	}
	free(token->str);
	if (line)
		token->str = ft_strdup(line);
	else
		token->str = ft_strdup("");
	printf("\n");
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
				i = check_env(token, i);
			}
			i++;
		}
		token = token->next;
	}
}
