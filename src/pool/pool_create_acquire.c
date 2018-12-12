#include <sys/mman.h>
#include <stdlib.h>
#include <stdint.h>
#include "macros_42.h"
#include "pool_42.h"

#define MMAP_PROT		(PROT_READ|PROT_WRITE)

#if defined(__APPLE__)
# define MMAP_FLAGS		(MAP_ANONYMOUS|MAP_PRIVATE)
#else
# define MMAP_FLAGS		(MAP_PRIVATE)
#endif

static inline void	*mmap_wrapper(size_t size)
{
	void	*p;

	p = mmap(NULL, size, MMAP_PROT, MMAP_FLAGS, -1, 0);
	if (p == MAP_FAILED)
		return (NULL);
	return (p);
}

t_pool				*pool_create(size_t pool_size, size_t elem_size)
{
	t_pool	*mapping;

	elem_size = ROUND_UP_8(elem_size);
	if (pool_size < (sizeof(t_pool) + elem_size))
		return (NULL);
	mapping = (t_pool*)mmap_wrapper(pool_size);
	if (mapping != NULL)
	{
		mapping->allocated_size = pool_size;
		mapping->max = (pool_size - sizeof(t_pool)) / elem_size;
		mapping->elem_size = elem_size;
		mapping->used = 0;
		mapping->offset = 0;
		mapping->freelist = NULL;
		mapping->next = NULL;
	}
	return (mapping);
}

static inline void	*get_unused_block_from_pool(t_pool *pool)
{
	void	*block;

	if (pool->freelist != NULL)
	{
		block = pool->freelist;
		pool->freelist = *(void**)block;
		pool->used += 1;
	}
	else if (pool->offset < pool->max)
	{
		block = (void*)((uintptr_t)pool + sizeof(t_pool)
				+ (pool->elem_size * pool->offset));
		pool->offset += 1;
		pool->used += 1;
	}
	else
	{
		block = NULL;
	}
	return (block);
}

void				*pool_acquire_block(t_pool **pool)
{
	t_pool	**ptr_to_pool;
	t_pool	*new_pool;
	void	*block;

	ptr_to_pool = pool;
	while (*ptr_to_pool != NULL)
	{
		block = get_unused_block_from_pool(*ptr_to_pool);
		if (block != NULL)
			return (block);
		ptr_to_pool = &((*ptr_to_pool)->next);
	}
	new_pool = pool_create((*pool)->allocated_size, (*pool)->elem_size);
	if (new_pool == NULL)
		return (NULL);
	*ptr_to_pool = new_pool;
	return (get_unused_block_from_pool(new_pool));
}
