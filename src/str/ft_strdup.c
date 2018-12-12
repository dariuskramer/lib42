#include <stddef.h>
#include <stdlib.h>
#include "memory_42.h"
#include "str_42.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	len;

	len = ft_strlen(s1);
	if ((str = (char *)malloc(len + 1)) == NULL)
		return (NULL);
	ft_memcpy(str, s1, len);
	str[len] = '\0';
	return (str);
}

char	*ft_strndup(const char *s1, size_t n)
{
	char	*str;
	size_t	len;

	len = ft_strnlen(s1, n);
	if ((str = (char *)malloc(len + 1)) == NULL)
		return (NULL);
	ft_memcpy(str, s1, len);
	str[len] = '\0';
	return (str);
}
