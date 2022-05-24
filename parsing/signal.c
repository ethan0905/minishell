/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:12:44 by achane-l          #+#    #+#             */
/*   Updated: 2022/05/24 13:49:17 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	control_c(int code)
{
	(void)code;
	if (g_signal.heredoc)
		return ;
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	if (g_signal.pid == 0)
		rl_redisplay();
}
