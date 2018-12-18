#include "list_42.h"

void	*list_push_front(t_list *list, const void *elem)
{
	t_list_node	*node;

	node = list_internal_new_node_with_copy(list, elem);
	if (node == NULL)
		return (NULL);
	node->prev = NULL;
	node->next = list->head;
	if (list->len == 0)
		list->tail = node;
	else
		list->head->prev = node;
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
	if (list->len == 0)
		list->head = node;
	else
		list->tail->next = node;
	list->tail = node;
	list->len += 1;
	return (LIST_NODE_DATA(node));
}
