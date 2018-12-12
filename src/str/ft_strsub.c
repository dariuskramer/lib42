#include <stddef.h>
#include <stdlib.h>
#include "memory_42.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;

	str = malloc(len + 1);
	if (str != NULL)
	{
		ft_memcpy(str, s + start, len);
		str[len] = '\0';
	}
	return (str);
}
