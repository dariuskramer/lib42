#include <stddef.h>
#include "pool_42.h"
#include "list_42.h"

t_list	*list_init(t_list *list, size_t elem_size)
{
	if (elem_size == 0)
		return (NULL);
	list->pool = pool_create(POOL_DEFAULT_SIZE, LIST_NODE_SIZE(elem_size));
	if (list->pool == NULL)
		return (NULL);
	list->head = NULL;
	list->tail = NULL;
	list->len = 0;
	list->elem_size = elem_size;
	return (list);
}

void	list_shutdown(t_list *list)
{
	pool_destroy(list->pool);
	list->pool = NULL;
	list->head = NULL;
	list->tail = NULL;
	list->len = 0;
	list->elem_size = 0;
}
