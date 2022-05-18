/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:23:19 by esafar            #+#    #+#             */
/*   Updated: 2022/05/18 18:41:05 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse(t_data *data, char *str)
{
	char *str_parse;

	if (ft_strlen(str) == 0)
		return (0);
	if (check_unclosed_quote(str))
	{
		printf("Error: unclosed quote.\n");
		fflush(stdout);
		return (0);
	}
	str_parse = expand_str(data, str);
	if (str_parse == NULL)
		return (0);
	if (!create_token_lst(data, str_parse))
	{
		free(str_parse);
		return (0);
	}
	free(str_parse);
	return (1);
}
