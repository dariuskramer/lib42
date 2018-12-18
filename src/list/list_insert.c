#include "list_42.h"

static void	internal_insert_at(t_list *list, size_t index, t_list_node *new)
{
	t_list_node	*current;

	current = list->head;
	while (index >= 1)
	{
		current = current->next;
		index -= 1;
	}
	current->prev->next = new;
	new->prev = current->prev;
	new->next = current;
	current->prev = new;
}

void	*list_insert_at(t_list *list, size_t index, const void *elem)
{
	t_list_node	*new_node;

	if (index >= list->len)
		return (NULL);
	if (index == 0)
		return (list_push_front(list, elem));
	new_node = list_internal_new_node_with_copy(list, elem);
	if (new_node == NULL)
		return (NULL);
	internal_insert_at(list, index, new_node);
	list->len += 1;
	return (LIST_NODE_DATA(new_node));
}
