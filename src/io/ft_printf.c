#include "io_42.h"
#define STDOUT_FD	(1)

static ssize_t	safe_write(const t_string *buf, int fd)
{
	char	*s;
	ssize_t	ret;
	size_t	writed;

	s = buf->str;
	writed = 0;
	while (writed < buf->len)
	{
		ret = write(fd, s + writed, buf->len - writed);
		if (ret == -1)
			return (-1);
		writed += (size_t)ret;
	}
	return ((ssize_t)writed);
}

ssize_t			ft_printf(const char *format, ...)
{
	va_list	ap;
	ssize_t	ret;

	va_start(ap, format);
	ret = ft_vprintf(format, ap);
	va_end(ap);
	return (ret);
}

ssize_t			ft_vprintf(const char *format, va_list ap)
{
	t_string	buf;

	if (string_init(&buf) == NULL)
		return (-1);
	if (ft_printf_fmt(&buf, format, ap) == NULL)
	{
		string_shutdown(&buf);
		return (-1);
	}
	return (safe_write(&buf, STDOUT_FD));
}

ssize_t			ft_dprintf(int fd, const char *format, ...)
{
	ssize_t	ret;
	va_list	ap;

	va_start(ap, format);
	ret = ft_vdprintf(fd, format, ap);
	va_end(ap);
	return (ret);
}

ssize_t			ft_vdprintf(int fd, const char *format, va_list ap)
{
	t_string	buf;

	if (string_init(&buf) == NULL)
		return (-1);
	if (ft_printf_fmt(&buf, format, ap) == NULL)
	{
		string_shutdown(&buf);
		return (-1);
	}
	return (safe_write(&buf, fd));
}
