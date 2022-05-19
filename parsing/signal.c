/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:12:44 by achane-l          #+#    #+#             */
/*   Updated: 2022/05/19 19:13:58 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	control_c(int code)
{
	(void)code;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	// printf("\033[0;31m➜ \033[0;33m❖\033[0;m \033[0;96 mminishell \033[0;m\033[0;33m❖ \033[0;m");
}

void	control_d(int code)
{
	(void)code;
//	printf("^\n");
//	printf("code ctrl + C: %d\n", code);
}
