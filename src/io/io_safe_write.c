#include <unistd.h>
#include <stddef.h>
#include "string_42.h"

ssize_t	io_safe_write(const t_string *buf, int fd)
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
