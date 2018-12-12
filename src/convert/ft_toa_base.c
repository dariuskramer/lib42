#include <stddef.h>
#include <malloc.h>
#include "macros_42.h"
#include "memory_42.h"
#include "str_42.h"

char	*ft_utoa_base_r(char *buf, unsigned long long n, unsigned base)
{
	char	*charset;
	size_t	i;

	if (base > 16)
		return (NULL);
	charset = "0123456789abcdef";
	i = 0;
	if (n == 0)
		buf[i++] = '0';
	while (n != 0)
	{
		buf[i++] = charset[n % base];
		n /= base;
	}
	buf[i] = '\0';
	return (ft_strrev(buf));
}

char	*ft_utoa_base(unsigned long long n, unsigned base)
{
	char	*s;

	if (base > 16)
		return (NULL);
	if ((s = malloc(128)) == NULL)
		return (NULL);
	ft_memset(s, 0x0, 128);
	return (ft_utoa_base_r(s, n, base));
}

char	*ft_stoa_base_r(char *buf, long long n, unsigned base)
{
	char	*charset;
	size_t	i;
	int		neg;

	if (base > 16)
		return (NULL);
	charset = "0123456789abcdef";
	i = 0;
	neg = (n < 0);
	if (n == 0)
		buf[i++] = '0';
	while (n != 0)
	{
		buf[i++] = charset[FT_ABS(n % base)];
		n /= base;
	}
	buf[i] = (neg) ? '-' : '\0';
	return (ft_strrev(buf));
}

char	*ft_stoa_base(long long n, unsigned base)
{
	char	*s;

	if (base > 16)
		return (NULL);
	if ((s = malloc(128)) == NULL)
		return (NULL);
	ft_memset(s, 0x0, 128);
	return (ft_stoa_base_r(s, n, base));
}
