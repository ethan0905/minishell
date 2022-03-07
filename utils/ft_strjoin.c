/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 13:50:42 by achane-l          #+#    #+#             */
/*   Updated: 2022/02/28 17:46:54 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"

static void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	size_t	i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	while (i < size)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}

static void	*ft_memmove(void *dest, const void *src, size_t size)
{
	unsigned char	*src2;

	if (!dest && !src)
		return (NULL);
	src2 = (unsigned char *)src;
	if (dest > src)
	{
		while (size--)
		{
			((unsigned char *)dest)[size] = src2[size];
		}
		return (dest);
	}
	ft_memcpy(dest, src, size);
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		ft_memmove(&str[i], &s1[i], 1);
		i++;
	}
	while (j < ft_strlen(s2))
	{
		ft_memmove(&str[i], &s2[j], 1);
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}