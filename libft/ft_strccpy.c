#include "libft.h"

char		*ft_strccpy(char *dst, char *str, int c)
{
	int			i;

	i = 0;
	while (str[i] && str[i] != c)
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
