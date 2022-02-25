/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:23:19 by esafar            #+#    #+#             */
/*   Updated: 2022/02/08 19:05:33 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quotes(char *str)
{
	int i;
	bool simple_quote;
	bool double_quote;

	i = 0;
	simple_quote = false;
	double_quote = false;
	while (str[i])
	{
		if (str[i] == '\'')
			simple_quote = !simple_quote;
		else if (str[i] == '\"')
		{
			double_quote = !double_quote;
		}
		i++;
	}
	if (simple_quote == false && double_quote == false)
		return (1);
	else
		return (0);
}
