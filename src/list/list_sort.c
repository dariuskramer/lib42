#include <stddef.h>
#include <stdbool.h>
#include "list_42.h"

inline static t_list_node	*get_tail(t_list_node *head)
{
	t_list_node	*node;

	node = head;
	while (node != NULL && node->next != NULL)
		node = node->next;
	return (node);
}

/*
** Return the middle node of the list `head`
** `head` stays the head
*/

inline static t_list_node	*split_in_half(t_list_node *head)
{
	t_list_node	*slow;
	t_list_node	*fast;
	t_list_node	*middle;

	slow = head;
	fast = head;
	while (fast->next != NULL && fast->next->next != NULL)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	middle = slow->next;
	slow->next = NULL;
	return (middle);
}

/*
** Merge 2 sorted lists together
*/

inline static t_list_node	*merge(t_list_node *a, t_list_node *b,
		t_list_compare compare)
{
	t_list_node	*new_head;
	t_list_node	**p;
	t_list_node	*prev;

	p = &new_head;
	prev = NULL;
	while (a != NULL && b != NULL)
	{
		if (compare(LIST_NODE_DATA(a), LIST_NODE_DATA(b)) < 0)
		{
			(*p) = a;
			a = a->next;
		}
		else
		{
			(*p) = b;
			b = b->next;
		}
		(*p)->prev = prev;
		prev = (*p);
		p = &(*p)->next;
	}
	(*p) = (a == NULL) ? b : a;
	(*p)->prev = prev;
	return (new_head);
}

inline static t_list_node	*merge_sort(t_list_node *head,
		t_list_compare compare)
{
	t_list_node	*second;

	if (head == NULL || head->next == NULL)
		return (head);
	second = split_in_half(head);
	head = merge_sort(head, compare);
	second = merge_sort(second, compare);
	head = merge(head, second, compare);
	return (head);
}

t_list						*list_sort(t_list *list, t_list_compare compare)
{
	list->head = merge_sort(list->head, compare);
	list->tail = get_tail(list->head);
	return (list);
}
