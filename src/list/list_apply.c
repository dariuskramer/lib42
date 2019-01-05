#include <stdlib.h>
#include <stdarg.h>
#include "list_42.h"

void	list_apply(t_list *list, t_list_apply f, ...)
{
	va_list		ap;
	t_list_node	*node;

	va_start(ap, f);
	node = list->head;
	while (node != NULL)
	{
		f(LIST_NODE_DATA(node), ap);
		node = node->next;
	}
	va_end(ap);
}
