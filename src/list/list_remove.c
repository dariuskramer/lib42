#include <stddef.h>
#include "pool_42.h"
#include "memory_42.h"
#include "list_42.h"

static t_list_node	*internal_remove_last(t_list *list)
{
	t_list_node	*node;

	node = list->head;
	list->head = NULL;
	list->tail = NULL;
	return (node);
}

static t_list_node	*internal_remove_head(t_list *list)
{
	t_list_node	*node;

	node = list->head;
	list->head = node->next;
	list->head->prev = NULL;
	return (node);
}

static t_list_node	*internal_remove_tail(t_list *list)
{
	t_list_node	*node;

	node = list->tail;
	list->tail = node->prev;
	list->tail->next = NULL;
	return (node);
}

static t_list_node	*internal_remove_node(t_list *list, size_t index)
{
	t_list_node	*node;

	node = list->head;
	while (index)
	{
		node = node->next;
		index -= 1;
	}
	node->prev->next = node->next;
	node->next->prev = node->prev;
	return (node);
}

t_list				*list_remove_at(t_list *list, size_t index, void *removed)
{
	t_list_node	*node;
	void		*data;

	if (index >= list->len)
		return (NULL);
	else if (list->len == 1)
		node = internal_remove_last(list);
	else if (index == 0)
		node = internal_remove_head(list);
	else if (index == list->len - 1)
		node = internal_remove_tail(list);
	else
		node = internal_remove_node(list, index);
	list->len -= 1;
	if (removed != NULL)
	{
		data = LIST_NODE_DATA(node);
		ft_memcpy(removed, data, list->elem_size);
		list->pool = pool_release_block(list->pool, node);
	}
	return (list);
}
