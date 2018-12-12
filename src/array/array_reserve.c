#include <stddef.h>
#include "structs_42.h"
#include "macros_42.h"
#include "memory_42.h"

t_array		*array_reserve(t_array *a, size_t additional)
{
	if (a->capacity - a->len < additional)
	{
		if (IS_POWER_OF_2(a->len + additional))
			a->capacity = a->len + additional;
		else
			a->capacity = next_power_of_2(a->len + additional);
		a->data = ft_realloc(a->data, a->capacity * a->elem_size,
								a->len * a->elem_size);
		if (a->data == NULL)
			return (NULL);
	}
	return (a);
}
