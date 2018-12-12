#include <stdlib.h>
#include "macros_42.h"

/*
** Source: http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
** Ex: 0100 0001
**	0100 0001 - 1	= 0100 0000
**	0100 0000 |>> 1	= 0110 0000
**	0110 0000 |>> 2	= 0111 1000
**	0111 1000 |>> 4	= 0111 1111
**	0111 1111 + 1	= 1000 0000
*/

size_t	next_power_of_2(size_t n)
{
	if (n == 0)
		return (1);
	if (IS_POWER_OF_2(n))
		return (n << 1);
	--n;
	n |= n >> 1;
	n |= n >> 2;
	n |= n >> 4;
	n |= n >> 8;
	n |= n >> 16;
	n |= n >> 32;
	return (n + 1);
}
