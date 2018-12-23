#include <stdarg.h>
#include "string_42.h"
#include "io_42.h"

t_string	*string_fmt(t_string *s, const char *format, ...)
{
	char	*ret;
	ssize_t	len;
	va_list	ap;

	va_start(ap, format);
	len = ft_vasprintf(&ret, format, ap);
	if (len == -1)
		return (NULL);
	va_end(ap);
	return (string_ncat(s, ret, (size_t)len));
}
