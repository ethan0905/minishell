/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_files.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:58:21 by achane-l          #+#    #+#             */
/*   Updated: 2022/05/24 01:56:05 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_FILES_H
# define EXEC_FILES_H
# include <fcntl.h>
# include <sys/wait.h>
# include "../minishell.h"
# include "../utils/utils.h"
# include "../get_next_line/get_next_line.h"
# include "../built-in/builtin.h"

typedef struct s_cmd
{
	bool			skip_cmd;
	int				infile;
	int				outfile;
	char			**cmd_param;
	struct s_cmd	*next;
}				t_cmd;

//utils_exec.c
int		here_doc(t_data *data, char *word);
void	print_error_command(char *cmd_name, int error_type);
void	select_and_exec(int save_stdout, t_data *data, t_cmd *cmd);
//get_cmds.c
int		count_arg_in_command(t_token *token);
char	**get_cmd(t_token *token);
// get_file.c
int		open_file(t_data *data, char *filename, int type);
int		get_infile(t_data *data, t_token *token);
int		get_outfile(t_token *token);
void	add_file_to_cmd(t_data *data, t_cmd *cmd, t_token *token);

// init_cmds.c
t_cmd	*create_cmd(t_data *data, t_token *token);
void	add_cmd(t_cmd *lst_cmd, t_cmd *new_cmd);
void	free_cmd(t_cmd **cmds);
t_cmd	*init_cmds(t_data *data, t_token *token);

// paths
int		check_env_val(char *src, char *find);
char	**init_paths(char **env);
int		check_path_cmd(t_cmd *my_cmd, char **paths);
// exec.c
bool	is_built_in(char *cmd);
bool	command_exist(t_data *data, t_cmd *cmd);
void	launch_built_in(t_data *data, t_cmd *cmd);
void	launch_cmd(t_data *data, t_cmd *cmd, int *fd);
int		exec(t_data *data);

//process
void	exit_process(t_data *data, int *fd);
void	redirect_in_out(t_cmd *cmd, int *fd);
void	child_process(t_data *data, t_cmd *cmd, int *fd);
void	parent_process(t_cmd *cmd, int *fd);
void	wait_all_and_finish(t_data *data, t_cmd *cmds);

#endif
