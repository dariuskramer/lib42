#include <stddef.h>
#include <stdlib.h>
#include "structs_42.h"
#include "string_42.h"

t_string	*string_create_with_capacity(size_t capacity)
{
	t_string	*s;

	s = malloc(sizeof(t_string));
	if (s == NULL)
		return (NULL);
	if (string_init_with_capacity(s, capacity) == NULL)
		return (NULL);
	return (s);
}

t_string	*string_create(void)
{
	return (string_create_with_capacity(STRING_INIT_SIZE - 1));
}

void		string_destroy(t_string *s)
{
	free(s->str);
	free(s);
}
