/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 09:04:02 by esafar            #+#    #+#             */
/*   Updated: 2022/05/23 17:36:02 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_isnewline(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*after_newline(char *save)
{
	size_t		i;
	size_t		j;
	char		*after_newline;

	i = 0;
	while (save[i] != '\0' && save[i] != '\n')
		i++;
	if (save[i] == '\0' || ft_strlen(save) - i <= 1)
	{
		free(save);
		return (NULL);
	}
	after_newline = (char *)malloc(sizeof(char) * (ft_strlen(save) - i + 1));
	if (!after_newline)
		return (NULL);
	i++;
	j = 0;
	while (save[i] != '\0')
		after_newline[j++] = save[i++];
	after_newline[j] = '\0';
	free(save);
	save = NULL;
	return (after_newline);
}

static char	*get_line(char *save)
{
	size_t	i;
	char	*line;

	i = 0;
	while (save[i] != '\0' && save[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (save[i] != '\0' && save[i] != '\n')
	{
		line[i] = save[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

int	get_next_line(int fd, char **line)
{
	int			ret;
	char		buff[BUFFER_SIZE + 1];
	char		*tmp;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE < 0 || !line || read(fd, "", 0) == -1)
		return (-1);
	if (!save)
		save = ft_strdup("");
	ret = 1;
	while (ft_isnewline(save) == 0 && ret != 0)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret == -1)
			return (-1);
		buff[ret] = '\0';
		tmp = save;
		save = ft_strjoin(save, buff);
		free(tmp);
	}
	*line = get_line(save);
	save = after_newline(save);
	if (ret == 0)
		return (0);
	return (1);
}
