#include "../minishell.h"

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
