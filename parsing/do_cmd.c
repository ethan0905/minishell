#include "../minishell.h"
/*
int	is_redirection(char *red)
{
	if ()
}*/

char	*get_redirection(char *actual)
{
	int i;

	i = 0;
	while (actual[i] && (actual[i] != '<' || actual[i] != '>'))
	{
		i++;
	}
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
