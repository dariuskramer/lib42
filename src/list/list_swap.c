#include "pool_42.h"
#include "memory_42.h"
#include "list_42.h"

t_list	*list_swap(t_list *list, size_t e1, size_t e2)
{
	t_list_node	*node1;
	t_list_node	*node2;
	void		*tmp;

	if (e1 >= list->len || e2 >= list->len)
		return (NULL);
	if (e1 == e2)
		return (list);
	tmp = pool_acquire_block(&list->pool);
	if (tmp == NULL)
		return (NULL);
	node1 = list_get_at(list, e1);
	node2 = list_get_at(list, e2);
	ft_memcpy(tmp, LIST_NODE_DATA(node1), list->elem_size);
	ft_memcpy(LIST_NODE_DATA(node1), LIST_NODE_DATA(node2), list->elem_size);
	ft_memcpy(LIST_NODE_DATA(node2), tmp, list->elem_size);
	pool_release_block(list->pool, tmp);
	return (list);
}
