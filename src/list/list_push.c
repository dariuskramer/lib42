#include "list_42.h"

void	*list_push_front(t_list *list, const void *elem)
{
	t_list_node	*node;

	node = list_internal_new_node_with_copy(list, elem);
	if (node == NULL)
		return (NULL);
	node->prev = NULL;
	node->next = list->head;
	list->head = node;
	list->len += 1;
	return (LIST_NODE_DATA(node));
}

void	*list_push_back(t_list *list, const void *elem)
{
	t_list_node	*node;

	node = list_internal_new_node_with_copy(list, elem);
	if (node == NULL)
		return (NULL);
	node->prev = list->tail;
	node->next = NULL;
	list->tail = node;
	list->len += 1;
	return (LIST_NODE_DATA(node));
}
