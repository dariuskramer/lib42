#include <stdbool.h>
#include "list_42.h"

t_list	*list_filter(const t_list *list, bool (*f)(void*))
{
	t_list		*new_list;
	t_list_node	*node;
	void		*data;

	new_list = list_create(list->elem_size);
	if (new_list == NULL)
		return (NULL);
	node = list->head;
	while (node != NULL)
	{
		data = LIST_NODE_DATA(node);
		if (f(data))
			if (list_push_back(new_list, data) == NULL)
			{
				list_destroy(new_list);
				return (NULL);
			}
		node = node->next;
	}
	return (new_list);
}
