#include <sys/types.h>
#include <stdint.h>
#include "structs_42.h"

ssize_t		array_index_of(const t_array *a, const void *e)
{
	uintptr_t	index;

	if (e >= a->data
		&& (uintptr_t)e < (uintptr_t)a->data + a->len * a->elem_size)
	{
		index = (uintptr_t)e - (uintptr_t)a->data;
		index /= a->elem_size;
		return ((ssize_t)index);
	}
	return (-1);
}
