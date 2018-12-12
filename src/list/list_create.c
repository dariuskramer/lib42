#include <stddef.h>
#include <stdlib.h>
#include "pool_42.h"
#include "list_42.h"

t_list	*list_create(size_t elem_size)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (list == NULL)
		return (NULL);
	if (list_init(list, elem_size) == NULL)
	{
		free(list);
		return (NULL);
	}
	return (list);
}

void	list_destroy(t_list *list)
{
	list_shutdown(list);
	free(list);
}
