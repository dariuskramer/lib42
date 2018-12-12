#include <stddef.h>
#include "structs_42.h"

t_string	*string_truncate(t_string *s, size_t n)
{
	if (n > s->len)
		return (NULL);
	s->len = n;
	s->str[s->len] = '\0';
	return (s);
}
