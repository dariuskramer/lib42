#include <stdlib.h>
#include "list_42.h"

void	list_apply(t_list *list, void (*f)(void*))
{
	t_list_node	*node;

	node = list->head;
	while (node != NULL)
	{
		f(LIST_NODE_DATA(node));
		node = node->next;
	}
}
