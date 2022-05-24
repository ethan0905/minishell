/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:23:19 by esafar            #+#    #+#             */
/*   Updated: 2022/05/24 12:45:11 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "built-in/builtin.h"
#include "utils/utils.h"
#include "exec_files/exec_files.h"

static void	init_data(t_data *data, char **env)
{
	data->envp = env;
	data->env = create_env(data->envp);
	data->test = convert_lst_to_tab(data);
	data->exit_code = 42;
	data->signal.pid = 42;
	signal(SIGINT, &control_c);
	signal(SIGQUIT, SIG_IGN);
}

static void	loop(t_data *data)
{
	char	*str;

	while (1)
	{
		str = readline("minishell > ");
		if (str == NULL)
		{
			free_tab_str(&data->test, -1);
			free_env(data->env);
			return ;
		}
		add_history(str);
		if ((ft_strlen(str) != 0) && parse(data, str))
		{
			data->cmd = init_cmds(data, data->begin);
			exec(data);
			free_token_lst(data);
		}
		free(str);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	init_data(&data, env);
	loop(&data);
	rl_clear_history();
	return (0);
}
