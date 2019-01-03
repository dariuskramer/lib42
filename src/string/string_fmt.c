#include <stdarg.h>
#include "string_42.h"
#include "io_42.h"

t_string	*string_fmt(t_string *s, const char *format, ...)
{
	va_list	ap;

	va_start(ap, format);
	if (io_fmt(s, format, ap) == NULL)
		return (NULL);
	va_end(ap);
	return (s);
}
