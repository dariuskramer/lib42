#include "array_42.h"

t_array		*array_truncate(t_array *a, size_t n)
{
	if (n > a->len)
		return (NULL);
	a->len = n;
	return (a);
}
