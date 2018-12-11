#ifndef POOL_42_H
# define POOL_42_H

# include <stdlib.h>
# include "structs_42.h"

# define POOL_SIZE		(4*4096)

/*
** `pool_create` allocates a new `t_pool` and initialize the intern fields
**
** `pool_destroy` desallocates the `t_pool`
*/
t_pool	*pool_create(size_t pool_size, size_t elem_size);
void	pool_destroy(t_pool *pool);

/*
** Return a free block from the 'pool'
** Either the head of the pool's freelist
** or the next unused block in the 'blocks' array.
** If everything is used, allocate a new pool
*/
void	*pool_acquire_block(t_pool **pool);

/*
** Add `block' to the head of the pool's freelist
** If the pool is empty and is not the only one, then `unmap` it
*/
t_pool	*pool_release_block(t_pool *pool, void *block);

#endif
