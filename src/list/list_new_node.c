#include "pool_42.h"
#include "memory_42.h"
#include "list_42.h"

t_list_node	*list_internal_new_node_with_copy(t_list *list, const void *elem)
{
	t_list_node	*new_node;
	void		*data;

	new_node = pool_acquire_block(&list->pool);
	if (new_node == NULL)
		return (NULL);
	data = LIST_NODE_DATA(new_node);
	ft_memcpy(data, elem, list->elem_size);
	return (new_node);
}
