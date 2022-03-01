/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_files.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:58:21 by achane-l          #+#    #+#             */
/*   Updated: 2022/02/28 15:21:19 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_FILES_H
# define EXEC_FILES_H
# define INFILE 1
# define HEREDOC 2
# define OUTFILE 3
# define A_OUTFILE 4
# define PIPE 5
#include "../minishell.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

typedef struct s_cmd
{
	int		*fd;
	int		*infile;
	int		*outfile;
	char	**cmd_param;
	struct s_cmd *next;
}				t_cmd;

//get_cmds.c

//error message
void	error_management(char *arg, int error);
//		exec
// ft_split
char	**ft_split(char *line, char sep);
// paths
int	check_env_val(char *src, char *find);
char	**init_paths(char **env);
int	check_path_cmd(t_cmd *my_cmd, char **paths);
// process
t_cmd	*init_cmds(t_token *token, int *fds);
//utils.c
int	ft_strlen(char *str);
void	*ft_memcpy(void *dest, const void *src, size_t size);
void	*ft_memmove(void *dest, const void *src, size_t size);
char	*ft_strjoin(char *s1, char *s2);
void	free_tab_str(char ***tab_str, int i);
#endif
