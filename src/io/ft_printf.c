#include <unistd.h>
#include "io_42.h"

ssize_t	ft_printf(const char *format, ...)
{
	va_list	ap;
	ssize_t	ret;

	va_start(ap, format);
	ret = ft_vprintf(format, ap);
	va_end(ap);
	return (ret);
}

ssize_t	ft_vprintf(const char *format, va_list ap)
{
	t_string	buf;

	if (string_init(&buf) == NULL)
		return (-1);
	if (io_fmt(&buf, format, ap) == NULL)
	{
		string_shutdown(&buf);
		return (-1);
	}
	return (io_safe_write(&buf, STDOUT_FILENO));
}

ssize_t	ft_dprintf(int fd, const char *format, ...)
{
	ssize_t	ret;
	va_list	ap;

	va_start(ap, format);
	ret = ft_vdprintf(fd, format, ap);
	va_end(ap);
	return (ret);
}

ssize_t	ft_vdprintf(int fd, const char *format, va_list ap)
{
	t_string	buf;

	if (string_init(&buf) == NULL)
		return (-1);
	if (io_fmt(&buf, format, ap) == NULL)
	{
		string_shutdown(&buf);
		return (-1);
	}
	return (io_safe_write(&buf, fd));
}
