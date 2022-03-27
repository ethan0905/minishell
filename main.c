/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:23:19 by esafar            #+#    #+#             */
/*   Updated: 2022/03/27 03:42:26 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	t_data data;
	char *str;

	(void)ac;
	(void)av;
	data.envp = env;
	data.env = create_env(data.envp);
	data.test = convert_lst_to_tab(&data);
	data.exit_code = 42;
	signal(SIGINT, &control_c);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		str = readline("\033[0;31m➜ \033[0;33m❖\033[0;m \033[0;96mminishell\033[0;m \033[0;33m❖ \033[0;m");
		if (str == NULL)
		{
			free_tab_str(&data.test, -1);
			free_env(data.env);
			return 0;
		}
		add_history(str);
		if ((ft_strlen(str) != 0) && parse(&data, str))
		{
			data.cmd = init_cmds(data.begin);
			exec(&data);
			free_lst(&data);
		}
		free(str);
	}
//	rl_clear_history();
	return (0);
}
