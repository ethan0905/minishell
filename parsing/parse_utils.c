/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:23:19 by esafar            #+#    #+#             */
/*   Updated: 2022/05/24 01:46:56 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../utils/utils.h"

static int	get_len_of_env_var(char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

char	*my_getenv(t_data *data, char *expand_to_search)
{
	int	i;
	int	expand_len;

	i = 0;
	expand_len = ft_strlen(expand_to_search);
	while (data->test[i])
	{
		if (ft_strncmp(expand_to_search, data->test[i], expand_len) == 0 && \
		get_len_of_env_var(data->test[i]) == expand_len)
			return (ft_strdup(data->test[i] + ft_strlen(expand_to_search) + 1));
		i++;
	}
	return (NULL);
}

int	check_unclosed_quote(char *str)
{
	int		i;
	bool	is_in_single_quote;
	bool	is_in_double_quote;

	i = 0;
	is_in_single_quote = false;
	is_in_double_quote = false;
	while (str[i])
	{
		if (str[i] == '\'' && !is_in_single_quote && !is_in_double_quote)
			is_in_single_quote = true;
		else if (str[i] == '\"' && !is_in_single_quote && !is_in_double_quote)
			is_in_double_quote = true;
		else if (str[i] == '\'' && is_in_single_quote && !is_in_double_quote)
			is_in_single_quote = false;
		else if (str[i] == '\"' && is_in_double_quote && !is_in_single_quote)
			is_in_double_quote = false;
		i++;
	}
	if (is_in_double_quote || is_in_single_quote)
		return (1);
	return (0);
}

void	add_char(char **actual, char c)
{
	int		i;
	char	*dest;

	dest = (char *)malloc(sizeof(char) * (ft_strlen(*actual) + 2));
	if (!dest)
		return ;
	i = 0;
	while ((*actual) && (*actual)[i] != '\0')
	{
		dest[i] = (*actual)[i];
		i++;
	}
	dest[i] = c;
	dest[i + 1] = '\0';
	if (*actual)
		free(*actual);
	(*actual) = dest;
}
