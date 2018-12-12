#include <stddef.h>
#include "memory_42.h"
#include "string_42.h"

t_string	*string_merge(t_string *dst, const t_string *a, const t_string *b)
{
	size_t		size;

	size = a->len + b->len;
	if (string_init_with_capacity(dst, size) == NULL)
		return (NULL);
	dst->len = a->len + b->len;
	ft_memcpy(dst->str, a->str, a->len);
	ft_memcpy(dst->str + a->len, b->str, b->len);
	dst->str[dst->len] = '\0';
	return (dst);
}
