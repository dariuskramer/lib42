#ifndef STRUCTS_42_H
# define STRUCTS_42_H

# include <stddef.h>

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

typedef struct	s_array
{
	void			*data;
	size_t			len;
	size_t			capacity;
	size_t			elem_size;
}				t_array;

#endif
