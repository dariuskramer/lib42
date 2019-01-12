#include "list_42.h"

static const void	*identity(const void *data)
{
	return (data);
}

t_list				*list_copy(const t_list *list)
{
	return (list_map(list, (t_list_map) & identity, list->elem_size));
}
