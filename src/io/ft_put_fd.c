#include <unistd.h>
#include <stdlib.h>
#include "str_42.h"
#include "convert_42.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char const *c, int fd)
{
	write(fd, c, ft_strlen(c));
}

void	ft_putendl_fd(char const *c, int fd)
{
	write(fd, c, ft_strlen(c));
	write(fd, "\n", 1);
}

void	ft_putnbr_fd(int nb, int fd)
{
	char	*s;

	s = ft_stoa_base(nb, 10);
	write(fd, s, ft_strlen(s));
	free(s);
}
