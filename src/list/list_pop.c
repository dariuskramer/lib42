#include "pool_42.h"
#include "list_42.h"

t_list	*list_pop_front(t_list *list, void *poped_elem)
{
	if (list->len == 0)
		return (NULL);
	return (list_remove_at(list, 0, poped_elem));
}

t_list	*list_pop_back(t_list *list, void *poped_elem)
{
	if (list->len == 0)
		return (NULL);
	return (list_remove_at(list, list->len - 1, poped_elem));
}
