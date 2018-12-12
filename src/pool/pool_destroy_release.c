#include <sys/mman.h>
#include <stdlib.h>
#include <stdint.h>
#include "pool_42.h"

static inline void	munmap_wrapper(void *p, size_t size)
{
	munmap(p, size);
}

void				pool_destroy(t_pool *pool)
{
	t_pool	*next;

	while (pool != NULL)
	{
		next = pool->next;
		munmap_wrapper(pool, pool->allocated_size);
		pool = next;
	}
}

t_pool				*pool_release_block(t_pool *pool, void *block)
{
	t_pool	**ptr_to_pool;
	t_pool	*node;

	ptr_to_pool = &pool;
	while (*ptr_to_pool != NULL)
	{
		node = *ptr_to_pool;
		if (block > (void*)node
				&& block < (void*)((uintptr_t)node + node->allocated_size))
		{
			*(void**)block = node->freelist;
			node->freelist = block;
			node->used -= 1;
			if (node->offset == node->max && node->used == 0)
			{
				*ptr_to_pool = node->next;
				munmap_wrapper(node, node->allocated_size);
			}
			break ;
		}
		ptr_to_pool = &((*ptr_to_pool)->next);
	}
	return (pool);
}
