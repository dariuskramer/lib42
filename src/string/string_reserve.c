#include <stddef.h>
#include "macros_42.h"
#include "memory_42.h"
#include "string_42.h"

t_string	*string_reserve(t_string *s, size_t additional)
{
	additional += 1;
	if (s->capacity - s->len < additional)
	{
		if (IS_POWER_OF_2(s->len + additional))
			s->capacity = s->len + additional;
		else
			s->capacity = next_power_of_2(s->len + additional);
		s->str = ft_realloc(s->str, s->capacity, s->len);
		if (s->str == NULL)
			return (NULL);
	}
	return (s);
}
