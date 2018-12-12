#include <stddef.h>
#include <stdint.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((const unsigned char*)s)[i] == (unsigned char)c)
			return ((void*)((uintptr_t)s + i));
		++i;
	}
	return (NULL);
}
