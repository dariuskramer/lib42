#include "array_42.h"

void	*array_get_available(t_array *a)
{
	if (array_reserve(a, 1) == NULL)
		return (NULL);
	a->len += 1;
	return (array_get_at(a, a->len - 1));
}
