#include <stddef.h>
#include "memory_42.h"
#include "list_42.h"

void	*list_get_at(const t_list *list, size_t index)
{
	t_list_node	*node;
	void		*data;

	if (index >= list->len)
		return (NULL);
	node = list->head;
	while (index)
	{
		node = node->next;
		index -= 1;
	}
	data = LIST_NODE_DATA(node);
	return (data);
}

void	*list_get_first(const t_list *list)
{
	void	*data;

	if (list->len == 0)
		return (NULL);
	data = LIST_NODE_DATA(list->head);
	return (data);
}

void	*list_get_last(const t_list *list)
{
	void	*data;

	if (list->len == 0)
		return (NULL);
	data = LIST_NODE_DATA(list->tail);
	return (data);
}

void	*list_set_at(t_list *list, size_t index, const void *elem)
{
	void	*data;

	if (index >= list->len)
		return (NULL);
	if (index == 0)
		data = list_get_first(list);
	else if (index == list->len - 1)
		data = list_get_last(list);
	else
		data = list_get_at(list, index);
	ft_memcpy(data, elem, list->elem_size);
	return (data);
}
