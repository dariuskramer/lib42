#include <stddef.h>
#include "list_42.h"

t_list	*list_uniq_sorted(const t_list *list, t_list_compare cmp)
{
	t_list		*uniq;
	t_list_node	*iter_node;

	uniq = list_create(list->elem_size);
	if (uniq == NULL || list->len == 0)
		return (uniq);
	iter_node = list->head;
	list_push_back(uniq, LIST_NODE_DATA(iter_node));
	while (iter_node != NULL)
	{
		if (cmp(LIST_NODE_DATA(uniq->tail), LIST_NODE_DATA(iter_node)) != 0)
			list_push_back(uniq, LIST_NODE_DATA(iter_node));
		iter_node = iter_node->next;
	}
	return (uniq);
}

t_list	*list_uniq_unsorted(const t_list *non_uniq, t_list_compare cmp)
{
	t_list		*uniq;
	t_list_node	*node;
	const void	*data;

	uniq = list_create(non_uniq->elem_size);
	if (uniq == NULL || non_uniq->len == 0)
		return (uniq);
	node = non_uniq->head;
	while (node != NULL)
	{
		data = LIST_NODE_DATA(node);
		if (list_contains(uniq, data, cmp) == false)
			list_push_back(uniq, data);
		node = node->next;
	}
	return (uniq);
}
