/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_files.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:58:21 by achane-l          #+#    #+#             */
/*   Updated: 2022/03/07 15:35:42 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_FILES_H
# define EXEC_FILES_H
#include "../minishell.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

typedef struct s_cmd
{
	bool	skip_cmd;
	int		infile;
	int		outfile;
	char	**cmd_param;
	struct s_cmd *next;
}				t_cmd;

//get_data_cmds.c
int	count_arg_in_command(t_token *token);
int	get_infile(t_token *token);
int	get_outfile(t_token *token);
char	**get_cmd(t_token *token);
// init_cmds.c
t_cmd	*create_cmd(t_token *token);
void	add_cmd(t_cmd *lst_cmd, t_cmd *new_cmd);
void	free_cmd(t_cmd **cmds);
t_cmd	*init_cmds(t_token *token);

// paths
int	check_env_val(char *src, char *find);
char	**init_paths(char **env);
int	check_path_cmd(t_cmd *my_cmd, char **paths);
// exec.c

//process
void	child_process(t_cmd *cmds, t_cmd *first, int *fd,char **env);
void	parent_process(t_cmd *cmds, int *fd);
void	wait_all_and_finish(t_cmd *cmds);

# endif