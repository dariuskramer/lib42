#include <stddef.h>
#include "structs_42.h"
#include "memory_42.h"
#include "array_42.h"

t_array		*array_insert_at(t_array *a, size_t i, const void *e)
{
	char	*src;

	if (i > a->len)
		return (NULL);
	if (array_reserve(a, 1) == NULL)
		return (NULL);
	if (i == a->len)
		return (array_push(a, e));
	src = array_get_at(a, i);
	ft_memmove(src + a->elem_size, src, (a->len - i) * a->elem_size);
	array_set_at(a, i, e);
	a->len += 1;
	return (a);
}
