#include <stddef.h>
#include "list_42.h"

#include <stdio.h>
t_list	*list_uniq_sorted(const t_list *list, t_list_compare cmp)
{
	t_list		*new;
	t_list_node	*iter_node;

	new = list_create(list->elem_size);
	if (new == NULL || list->len == 0)
		return (new);
	iter_node = list->head;
	list_push_back(new, LIST_NODE_DATA(iter_node));
	while (iter_node != NULL)
	{
		if (cmp(LIST_NODE_DATA(new->tail), LIST_NODE_DATA(iter_node)) != 0)
			list_push_back(new, LIST_NODE_DATA(iter_node));
		iter_node = iter_node->next;
	}
	return (new);
}

t_list	*list_uniq_unsorted(const t_list *list, t_list_compare cmp)
{
	t_list	*uniq_sorted;
	t_list	*non_uniq;

	non_uniq = list_copy(list);
	if (non_uniq == NULL)
		return (NULL);
	non_uniq = list_sort(non_uniq, cmp);
	uniq_sorted = list_uniq_sorted(non_uniq, cmp);
	list_destroy(non_uniq);
	return (uniq_sorted);
}
