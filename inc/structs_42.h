#ifndef STRUCTS_42_H
# define STRUCTS_42_H

# include <stdlib.h>

typedef struct	s_pool
{
	size_t			allocated_size;
	size_t			max;
	size_t			elem_size;
	size_t			used;
	size_t			offset;
	void			*freelist;
	struct s_pool	*next;
}				t_pool;

#endif
