#include <stdio.h>
#inclue "list_42.h"

void print_list_on_line(t_list_node *node)
{
	printf("[");
	for (; node; node = node->next)
	{
		printf("%d", *(int*)LIST_NODE_DATA(node));
		if (node->next) printf(", ");
	}
	printf("]");
}

void print_full_list(t_list_node *node)
{
	printf("HEAD\n");
	for (; node; node = node->next)
	{
		if (node->prev == NULL) printf("NULL");
		else printf("[%d]", *(int*)LIST_NODE_DATA(node->prev));

		printf(" <- [%d] -> ", *(int*)LIST_NODE_DATA(node));

		if (node->next == NULL) printf("NULL\n");
		else printf("[%d]\n", *(int*)LIST_NODE_DATA(node->next));
	}
	printf("TAIL\n");
}
