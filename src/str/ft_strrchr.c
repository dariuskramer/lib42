#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>
#include "str_42.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	len = ft_strlen(s);
	if (c == '\0')
		return ((char*)((uintptr_t)s + len));
	while (len--)
		if (s[len] == c)
			return ((char*)((uintptr_t)s + len));
	return (NULL);
}

ssize_t	ft_strrchrpos(const char *s, int c)
{
	char	*p;

	p = ft_strrchr(s, c);
	if (p == NULL)
		return (-1);
	return ((ssize_t)(p - s));
}

char	*ft_strrnchr(const char *s, int c, size_t n)
{
	size_t	len;

	len = ft_strlen(s);
	while (n--)
	{
		if (s[len] == c)
			return ((char*)((uintptr_t)s + len));
		--len;
	}
	return (NULL);
}

ssize_t	ft_strrnchrpos(const char *s, int c, size_t n)
{
	char	*p;

	p = ft_strrnchr(s, c, n);
	if (p == NULL)
		return (-1);
	return ((ssize_t)(p - s));
}
