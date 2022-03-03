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
	char *line;

	dest = NULL;
	line = NULL;
	if (token->str[0] != '\\')
		i++;
	printf("VOICI CE QUI EST STOCKE DANS STR = %s\n", token->str);
	printf("str[i]= %c\n", token->str[i]);
	while(token->str && token->str[i] != '\0' && token->str[i] != ' ')
		add_char(&dest, token->str[i++]);
	printf("DEST: %s\n", dest);
	if (token->str[0] != '\\')
		line = getenv(dest);
	else
		line = ft_strdup(dest);
	free(token->str);
	if (line)
		token->str = ft_strdup(line);
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
				i = check_env(token, i);
			}
			i++;
		}
		token = token->next;
	}
}
