#include "pool_42.h"
#include "memory_42.h"
#include "list_42.h"

t_list	*list_swap(t_list *list, size_t e1, size_t e2)
{
	void	*data1;
	void	*data2;
	void	*tmp;

	if (e1 >= list->len || e2 >= list->len)
		return (NULL);
	if (e1 == e2)
		return (list);
	tmp = pool_acquire_block(&list->pool);
	if (tmp == NULL)
		return (NULL);
	data1 = list_get_at(list, e1);
	data2 = list_get_at(list, e2);
	ft_memcpy(tmp, data1, list->elem_size);
	ft_memcpy(data1, data2, list->elem_size);
	ft_memcpy(data2, tmp, list->elem_size);
	pool_release_block(list->pool, tmp);
	return (list);
}
