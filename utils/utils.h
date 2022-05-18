/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 18:49:27 by esafar            #+#    #+#             */
/*   Updated: 2022/05/18 15:36:34 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
#include "../minishell.h"

int	ft_strlen(char *str);
char	*ft_strdup(char *str);
void	free_tab_str(char ***tab_str, int i);
char	**ft_split(char *line, char sep);
int	ft_strcmp(char *s1, char *s2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_itoa(int nb);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char *s, int start, int len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strcopy(char *src);
//env_utils
int     ft_lstlen(t_env *lst);
char    **convert_lst_to_tab(t_data *data);
t_env	*create_env_line(char *line);
t_env	*create_env(char **env);
void    free_env(t_env *env);
#endif
