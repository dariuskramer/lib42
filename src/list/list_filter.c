#include <stdbool.h>
#include <stdarg.h>
#include "list_42.h"

t_list	*list_filter(const t_list *list, t_list_filter f, ...)
{
	va_list		ap;
	t_list		*new_list;
	t_list_node	*node;
	void		*data;

	va_start(ap, f);
	new_list = list_create(list->elem_size);
	if (new_list == NULL)
		return (NULL);
	node = list->head;
	while (node != NULL)
	{
		data = LIST_NODE_DATA(node);
		if (f(data, ap))
		{
			if (list_push_back(new_list, data) == NULL)
			{
				list_destroy(new_list);
				return (NULL);
			}
		}
		node = node->next;
	}
	va_end(ap);
	return (new_list);
}
