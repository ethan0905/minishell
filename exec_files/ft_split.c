/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 13:54:19 by achane-l          #+#    #+#             */
/*   Updated: 2022/02/21 14:11:11 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec_files.h"

static int	count_words(char *line, char sep)
{
	int	nb_words;
	int	i;

	i = 0;
	nb_words = 0;
	while (line && line[i])
	{
		if (i > 0 && line[i] == sep && line[i - 1] != sep)
			nb_words++;
		i++;
	}
	if (line && i > 0 && line[i] == 0 && line[i - 1] != sep)
		nb_words++;
	return (nb_words);
}

static int	str_append(char **str, char carac)
{
	char	*new_str;
	int		len;

	len = (int)ft_strlen(*str);
	new_str = malloc(len + 2);
	if (new_str == NULL)
		return (-1);
	new_str[len + 1] = 0;
	new_str[len] = carac;
	while (*str && len > 0)
	{
		new_str[len - 1] = (*str)[len - 1];
		len--;
	}
	if (*str)
		free(*str);
	*str = new_str;
	return (0);
}

static void	init_tab(char ***tab_str, int tab_size)
{
	int	i;

	i = 0;
	while (i < tab_size)
	{
		(*tab_str)[i] = NULL;
		i++;
	}
}

char	**ft_split(char *line, char sep)
{
	char	**tab_str;
	int		nb_words;
	int		i;

	i = 0;
	nb_words = count_words(line, sep);
	tab_str = (char **)malloc(sizeof(char *) * (nb_words + 1));
	if (tab_str == NULL)
		return (NULL);
	init_tab(&tab_str, nb_words + 1);
	while (line && *line)
	{
		if (*line != sep)
		{
			if (str_append(&tab_str[i], *line) == -1)
			{
				free_tab_str(&tab_str, i);
				return (NULL);
			}
		}
		else if (*line == sep && tab_str[i] != NULL)
			i++;
		line++;
	}
	return (tab_str);
}