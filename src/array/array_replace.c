#include <stddef.h>
#include "memory_42.h"
#include "array_42.h"

t_array		*array_replace_at(t_array *a, size_t i, const void *e, void *old)
{
	void	*p;

	if (i >= a->len)
		return (NULL);
	if (old != NULL)
	{
		p = array_get_at(a, i);
		ft_memcpy(old, p, a->elem_size);
	}
	array_set_at(a, i, e);
	return (a);
}
