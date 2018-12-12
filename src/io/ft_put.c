#include <unistd.h>
#include <stdlib.h>
#include "str_42.h"
#include "convert_42.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char const *c)
{
	write(1, c, ft_strlen(c));
}

void	ft_putendl(char const *c)
{
	write(1, c, ft_strlen(c));
	write(1, "\n", 1);
}

void	ft_putnbr(int n)
{
	char	*s;

	s = ft_stoa_base(n, 10);
	write(1, s, ft_strlen(s));
	free(s);
}
