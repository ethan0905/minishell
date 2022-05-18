/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:56:36 by achane-l          #+#    #+#             */
/*   Updated: 2022/05/18 15:38:52 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

//# define PURPLE \033[0;35m
// # define YELLOW \033[0;33m
// # define END \033[0;m

#include "../minishell.h"

int     ft_pwd(void);
int	    ft_env(char **env);
//export et export utils
int	    ft_export(t_data *data, char *str);
char    *get_syntax(char *str);
int     env_line_already_exist(t_data *data, t_env *new);
void	add_env_line(t_env *env, t_env *new);

void	free_env(t_env *env);
int     ft_unset(t_data *data, char *str);
int     ft_echo(char **args);
int     ft_cd(t_data *data, char **params);
void	ft_exit(t_data *data, struct s_cmd *cmd);

#endif
