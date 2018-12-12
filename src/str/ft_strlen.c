#include <stddef.h>
#include <stdint.h>
#include "memory_42.h"

size_t	ft_strlen(const char *s)
{
	return ((uintptr_t)(ft_memchr(s, (int)'\0', ~0ULL)) - (uintptr_t)s);
}

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	void	*result;

	if ((result = ft_memchr(s, (int)'\0', maxlen)))
		return ((uintptr_t)result - (uintptr_t)s);
	return (maxlen);
}
