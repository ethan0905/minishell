<<<<<<< HEAD
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void	add_char(char **actual, char c);
/*
int	ft_strlen(char *str)
{
	int i = 0;

	while (str && str[i])
		i++;
	return (i);
}

t_lst *create_cmd(char *str)
{
	t_lst *new;

	new =(t_lst *)malloc(sizeof(t_lst));
	if (!new)
		return (NULL);
	new->tmp = str;
	return (new);
}

t_lst	*get_end(t_lst *lst_cmd)
{
	while (lst_cmd && lst_cmd->next != NULL)
		lst_cmd = lst_cmd->next;
	return (lst_cmd);
}

char	*remove_front_space(char *actual)
{
	int i;
	int count;
	char *dest;

	count = 0;
	while (actual[count] == ' ')
		count++;
	i = 0;
	while (actual[i + count] != '\0')
		i++;
	dest = (char *)malloc(sizeof(char) * (ft_strlen(actual) - count + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (actual[i + count] != '\0')
	{
		dest[i] = actual[i + count];
		i++;
	}
	dest[i] = '\0';
//	if (actual)
//		free(actual);
	return (dest);
}

char	*remove_end_space(char *actual)
{
	int i;
	int count;
	char *dest;

	i = 0;
	while (actual[i] != '\0')
		i++;
	count = 0;
	while (i > 0 && actual[i - 1] == ' ')
	{
		i--;
		count++;
	}
	dest = (char *)malloc(sizeof(char) * (ft_strlen(actual) - count + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (actual[i] != '\0' && i < (ft_strlen(actual) - count))
	{
		dest[i] = actual[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	add_cmd(char *actual, t_data *data)
{
	t_lst *new;

	actual = remove_front_space(actual);
	actual = remove_end_space(actual);
	printf("tmp : [%s]\n", actual);
	new = create_cmd(actual);
	if (!new)
		return;
	if (!data->lst_cmd)
		data->lst_cmd = new;
	else
		get_end(data->lst_cmd)->next = new;
}

void	add_char(char **actual, char c)
{
	int i;
	char *dest;

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

void	free_lst(t_data *data)
{
	t_lst *lst;

	while (data->lst_cmd)
	{
		lst = data->lst_cmd;
		if (data->lst_cmd->tmp)
			free(data->lst_cmd->tmp);
		data->lst_cmd = data->lst_cmd->next;
		if (lst)
			free(lst);
		printf("FREE\n");
	}
}
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:23:19 by esafar            #+#    #+#             */
/*   Updated: 2022/02/08 19:05:33 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
>>>>>>> ethan

int main(void)
{
	t_data data;
<<<<<<< HEAD
	char *actual = NULL;
	int i = 0;
	bool double_quote;
	bool simple_quote;

	data.nb_cmd = 0;
	data.lst_cmd = NULL;
	simple_quote = false;
	double_quote = false;

	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			simple_quote = !simple_quote;
		if (str[i] == '\"')
			double_quote = !double_quote;
		if (str[i] == '|' && !simple_quote && !double_quote)
		{
			add_cmd(actual, &data);
			actual = NULL;
			data.nb_cmd++;
			i++;
		}
		if (str[i] != '\0')
			add_char(&actual, str[i]);
		i++;
	}
	if (actual)
	{
		add_cmd(actual, &data);
		//free(actual); //checker if need to free or not
		actual = NULL;
		data.nb_cmd++;
	}
	free_lst(&data);
	return (0);
}
*/
int main()
{
=======
>>>>>>> ethan
	char *str;

	data.end = false;
	while (data.end == false)
	{
		str = readline("\033[0;31m➜ \033[0;33m❖\033[0;m \033[0;96mminishell\033[0;m \033[0;33m❖ \033[0;m");
<<<<<<< HEAD
		printf("str = %s\n", str);
		do_cmd(str);
=======
>>>>>>> ethan
		add_history(str);
		parse(&data, str);
		free(str);
	}
	return (0);
}
