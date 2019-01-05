#include <stddef.h>
#include <stdbool.h>
#include "list_42.h"

t_list	*list_sort(t_list *list, t_list_compare compare)
{
	void	*e1;
	void	*e2;
	size_t	i;
	bool	swapped;

	swapped = true;
	while (swapped == true)
	{
		swapped = false;
		i = 1;
		while (i < list->len)
		{
			e1 = list_get_at(list, i - 1);
			e2 = list_get_at(list, i);
			if (compare(e1, e2) > 0)
			{
				if (list_swap(list, i - 1, i) == NULL)
					return (NULL);
				swapped = true;
			}
			i += 1;
		}
	}
	return (list);
}
