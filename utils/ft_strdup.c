#include "utils.h"

char	*ft_strdup(char *src)
{
	size_t	i;
	char	*dest;

	i = 0;
	dest = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!dest)
		return (NULL);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
