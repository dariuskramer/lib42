#include <stddef.h>
#include <sys/types.h>
#include "memory_42.h"
#include "array_42.h"

t_array		*array_remove_at(t_array *a, size_t i, void *removed)
{
	char	*p;
	size_t	len;

	if (i >= a->len)
		return (NULL);
	p = array_get_at(a, i);
	if (removed != NULL)
		ft_memcpy(removed, p, a->elem_size);
	a->len -= 1;
	len = (a->len - i) * a->elem_size;
	ft_memmove(p, p + a->elem_size, len);
	return (a);
}

t_array		*array_remove_elem(t_array *a, const void *e)
{
	ssize_t		index;

	index = array_index_of(a, e);
	if (index == -1)
		return (NULL);
	return (array_remove_at(a, (size_t)index, NULL));
}
