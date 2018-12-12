#include <stddef.h>
#include <stdlib.h>
#include "error_42.h"

/*
** Standard 7.20.3: malloc(0)
** If the size of the space requested is zero,
** the behavior is implementation- deﬁned: either a null pointer is returned,
** or the behavior is as if the size were some nonzero value,
** except that the returned pointer shall not be used to access an object.
*/

void	*malloc_or_die(size_t size)
{
	void	*p;

	p = malloc(size);
	if (p == NULL)
		die(FATAL_MALLOC);
	return (p);
}
