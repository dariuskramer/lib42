#include <stddef.h>
#include "memory_42.h"
#include "string_42.h"

/*
** Append the char 'c', 'n' times, to the buffer
*/

t_string	*string_set(t_string *s, int c, size_t n)
{
	if (string_reserve(s, n + 1) == NULL)
		return (NULL);
	ft_memset(s->str + s->len, c, n);
	s->len += n;
	s->str[s->len] = 0;
	return (s);
}
