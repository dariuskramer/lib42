#include <stddef.h>
#include "structs_42.h"
#include "array_42.h"

void	*array_find_from(t_array set, size_t n,
		int (match)(const void *elem, const void *param), const void *param)
{
	void	*elem;

	while ((elem = array_get_at(&set, n++)) != NULL)
		if (match(elem, param))
			return (elem);
	return (NULL);
}

void	*array_find(t_array set,
		int (match)(const void *elem, const void *param), const void *param)
{
	return (array_find_from(set, 0, match, param));
}
