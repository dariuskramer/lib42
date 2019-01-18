#include <stdbool.h>
#include "list_42.h"

bool	list_contains(const t_list *list, const void *elem, t_list_compare cmp)
{
	t_list_node	*node;
	const void	*data;

	node = list->head;
	while (node != NULL)
	{
		data = LIST_NODE_DATA(node);
		if (cmp(data, elem) == 0)
			return (true);
		node = node->next;
	}
	return (false);
}
