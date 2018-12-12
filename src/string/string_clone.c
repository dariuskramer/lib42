#include "string_42.h"

t_string	*string_clone(t_string *dst, const t_string *src)
{
	return (string_init_ndup(dst, src->str, src->len));
}
