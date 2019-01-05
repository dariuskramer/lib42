#include <stddef.h>
#include <stdarg.h>
#include "list_42.h"

void	*list_fold_left(const t_list *list, t_list_fold f, void *init_val,
		...)
{
	va_list		ap;
	t_list_node	*node;
	void		*accumulator;

	va_start(ap, init_val);
	accumulator = init_val;
	node = list->head;
	while (node != NULL)
	{
		accumulator = f(accumulator, LIST_NODE_DATA(node), ap);
		if (accumulator == NULL)
			return (NULL);
		node = node->next;
	}
	va_end(ap);
	return (accumulator);
}
