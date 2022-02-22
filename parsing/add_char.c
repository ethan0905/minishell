#include "../minishell.h"

void	add_char(char **actual, char c)
{
	int i;
	char *dest;

	dest = (char *)malloc(sizeof(char) * (ft_strlen(*actual) + 2));
	if (!dest)
		return ;
	i = 0;
	while ((*actual) && (*actual)[i] != '\0')
	{
		dest[i] = (*actual)[i];
		i++;
	}
	dest[i] = c;
	dest[i + 1] = '\0';
	if (*actual)
		free(*actual);
	(*actual) = dest;
}
