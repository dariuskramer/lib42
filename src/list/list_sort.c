#include <stddef.h>
#include "list_42.h"

t_list	*list_sort(t_list *list, t_list_compare compare)
{
	t_list_node	*e1;
	t_list_node	*e2;
	size_t		i;
	size_t		j;

	i = 0;
	while (i < list->len)
	{
		j = 0;
		while(j < list->len - i - 1)
		{
			e1 = list_get_at(list, j);
			e2 = list_get_at(list, j + 1);
			if (compare(e1, e2) > 0)
				list_swap(list, j, j + 1);
			j += 1;
		}
		i -= 1;
	}
	return (list);
}
