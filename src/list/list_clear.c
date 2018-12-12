#include "list_42.h"

t_list	*list_clear(t_list *list)
{
	size_t elem_size;

	elem_size = list->elem_size; 
	list_shutdown(list);
	return (list_init(list, elem_size));
}
