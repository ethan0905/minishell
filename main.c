#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

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

void	add_cmd(char *actual, t_data *data)
{
	t_lst *new;

//	printf("addcmd: %p\n", actual);
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
/*
void	free_lst(t_data *data)
{
	while (data->lst_cmd)
}*/
/*
int	is_space(char *str, int i)
{
	while (str && str[i] && str[i] == ' ')
		i++;
	return (i);
}*/

int	do_cmd(char *str)
{
	t_data data;
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
			printf("tmp: [%s]\n", actual);
			add_cmd(actual, &data);
			actual = NULL;
			data.nb_cmd++;
			i++;
//			i = is_space(str, i);
		}
		if (str[i] != '\0')
			add_char(&actual, str[i]);
		i++;
	}
	if (actual)
	{
		printf("tmp: [%s]\n", actual);
		add_cmd(actual, &data);
		//free(actual); //checker if need to free or not
		actual = NULL;
		data.nb_cmd++;
	}
//	free_lst(&data);
	return (0);
}

int main()
{
	char *str;

	while (1)
	{
		str = readline("\033[0;31m➜ \033[0;33m❖\033[0;m \033[0;96mℳιηι$ℎєᏝᏝ\033[0;m \033[0;33m❖ \033[0;m");
		printf("str = %s\n", str);
		do_cmd(str);
		add_history(str);
		free(str);
	}
	return (0);
}
