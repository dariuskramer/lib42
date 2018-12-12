#include "memory_42.h"
#include "array_42.h"

t_array		*array_clone(t_array *dst, const t_array *src)
{
	if (array_init_with_capacity(dst, src->capacity, src->elem_size) == NULL)
		return (NULL);
	dst->len = src->len;
	ft_memcpy(dst->data, src->data, src->len * src->elem_size);
	return (dst);
}
