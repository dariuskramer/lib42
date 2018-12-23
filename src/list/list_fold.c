#include <stddef.h>
#include "list_42.h"

void	*list_fold_left(const t_list *list, void *(*f)(void*, void*),
		void *init_val)
{
	t_list_node	*node;
	void		*accumulator;

	accumulator = init_val;
	node = list->head;
	while (node != NULL)
	{
		accumulator = f(accumulator, LIST_NODE_DATA(node));
		if (accumulator == NULL)
			return (NULL);
		node = node->next;
	}
	return (accumulator);
}
