#include <stddef.h>
#include "memory_42.h"
#include "array_42.h"

void	*array_get_at(const t_array *a, size_t i)
{
	if (i < a->len)
		return ((char *)a->data + i * a->elem_size);
	return (NULL);
}

void	*array_set_at(t_array *a, size_t i, const void *e)
{
	if (i < a->len)
		return (ft_memcpy(array_get_at(a, i), e, a->elem_size));
	return (NULL);
}

void	*array_get_last(const t_array *a)
{
	if (a->len == 0)
		return (NULL);
	return (array_get_at(a, a->len - 1));
}

void	*array_get_first(const t_array *a)
{
	if (a->len > 0)
		return (array_get_at(a, 0));
	return (NULL);
}
