/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:06:12 by achane-l          #+#    #+#             */
/*   Updated: 2022/03/01 17:12:38 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec_files.h"

int	exec(t_token *token, char **env)
{
	t_cmd	*cmds;
	int		fd[2];

	init_cmds(token, fd);
	
}
