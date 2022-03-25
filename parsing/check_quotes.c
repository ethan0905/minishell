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

void	init_quote_struct(t_quote *quote)
{
	quote->lock = 0;
	quote->simpleq = false;
	quote->doubleq = false;
}

int	open_or_close(t_quote *quote)
{
	if (quote->simpleq || quote->doubleq)
		return (0);
	return (1);
}

int	check_unclosed_quote(char *str)
{
	int i;
	t_quote quote;

	i = -1;
	init_quote_struct(&quote);
	while (str[++i])
	{
		if (quote.lock == 0 && (str[i] == '\'' || str[i] == '\"') && (str[i-1] && str[i-1] != '\\'))
		{
			if (str[i] == '\'')
				quote.simpleq = !quote.simpleq;
			else if (str[i] == '\"')
				quote.doubleq = !quote.doubleq;
			quote.lock = 1;
		}
		else if (quote.lock == 1 && ((str[i] == '\'' && quote.simpleq ) || (str[i] == '\"' && quote.doubleq)) && (str[i-1] && str[i-1] != '\\'))
		{
			if (quote.simpleq && str[i] == '\'')
				quote.simpleq = !quote.simpleq;
			else if (quote.doubleq && str[i] == '\"')
				quote.doubleq = !quote.doubleq;
			quote.lock = 0;
		}
	}
	return (open_or_close(&quote));
}

/*
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
}*/
