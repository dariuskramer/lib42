#include <stddef.h>
#include <stdarg.h>
#include "list_42.h"

t_list	*list_map(const t_list *list, t_list_map f, size_t new_elem_size,
		...)
{
	va_list		ap;
	t_list		*new_list;
	t_list_node	*node;
	void		*new_data;

	va_start(ap, new_elem_size);
	new_list = list_create(new_elem_size);
	if (new_list == NULL)
		return (NULL);
	node = list->head;
	while (node != NULL)
	{
		new_data = f(LIST_NODE_DATA(node), ap);
		if (new_data == NULL)
		{
			list_destroy(new_list);
			return (NULL);
		}
		list_push_back(new_list, new_data);
		node = node->next;
	}
	va_end(ap);
	return (new_list);
}
