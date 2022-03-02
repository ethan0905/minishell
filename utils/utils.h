/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 18:49:27 by esafar            #+#    #+#             */
/*   Updated: 2022/02/28 17:48:11 by achane-l         ###   ########.fr       */
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
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
#endif
