#include <stddef.h>
#include "structs_42.h"
#include "memory_42.h"
#include "str_42.h"
#include "string_42.h"

t_string	*string_ncat(t_string *s, const char *str, size_t len)
{
	if (string_reserve(s, len) == NULL)
		return (NULL);
	ft_memcpy(s->str + s->len, str, len);
	s->len += len;
	s->str[s->len] = '\0';
	return (s);
}

t_string	*string_cat(t_string *s, const char *str)
{
	return (string_ncat(s, str, ft_strlen(str)));
}

t_string	*string_append(t_string *dst, const t_string *src)
{
	return (string_ncat(dst, src->str, src->len));
}
