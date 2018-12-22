#include <stddef.h>
#include "list_42.h"

#include <stdio.h>
t_list	*list_map(const t_list *list, void *(*f)(void*), size_t new_elem_size)
{
	t_list		*new_list;
	t_list_node	*node;
	void		*new_data;

	new_list = list_create(new_elem_size);
	if (new_list == NULL)
		return (NULL);
	node = list->head;
	while (node != NULL)
	{
		new_data = f(LIST_NODE_DATA(node));
		if (new_data == NULL)
		{
			list_destroy(new_list);
			return (NULL);
		}
		list_push_back(new_list, new_data);
		node = node->next;
	}
	return (new_list);
}
