#include "libft.h"

size_t		ft_clength(char *str, int c)
{
	int			i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}
