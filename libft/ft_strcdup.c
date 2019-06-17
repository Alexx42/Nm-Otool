#include "libft.h"

char    *ft_strcdup(const char *s1, int c)
{
        char    *cpy;
        int             i;
        int             j;

        j = 0;
        i = 0;
        while (s1[i])
                i++;
        if ((cpy = malloc(sizeof(char) * i + 1)) == NULL)
                return (NULL);
        while (s1[j] && s1[j] != c)
        {
                cpy[j] = s1[j];
                j++;
        }
        cpy[j] = '\0';
        return (cpy);
}
