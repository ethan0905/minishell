#include "../minishell.h"

char	*remove_front_space(char *actual)
{
	int i;
	int count;
	char *dest;

	count = 0;
	while (actual[count] == ' ')
		count++;
	i = 0;
	while (actual[i + count] != '\0')
		i++;
	dest = (char *)malloc(sizeof(char) * (ft_strlen(actual) - count + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (actual[i + count] != '\0')
	{
		dest[i] = actual[i + count];
		i++;
	}
	dest[i] = '\0';
//	if (actual)
//		free(actual);
	return (dest);
}

char	*remove_end_space(char *actual)
{
	int i;
	int count;
	char *dest;

	i = 0;
	while (actual[i] != '\0')
		i++;
	count = 0;
	while (i > 0 && actual[i - 1] == ' ')
	{
		i--;
		count++;
	}
	dest = (char *)malloc(sizeof(char) * (ft_strlen(actual) - count + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (actual[i] != '\0' && i < (ft_strlen(actual) - count))
	{
		dest[i] = actual[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
