#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "unity.h"
#include "list_42.h"

static t_list *list;

void setUp(void)
{
}

void tearDown(void)
{
	list_destroy(list);
}

int	compare_int(int *a, int *b)
{
	return (*a - *b);
}

void test_ListSort_EmptyList(void)
{
	list = list_create(sizeof(int));


	void *ret = list_sort(list, (t_list_compare)&compare_int);

	TEST_ASSERT_EQUAL(0, list->len);
	TEST_ASSERT_NOT_NULL(ret);
	TEST_ASSERT_EQUAL_PTR(list, ret);
	TEST_ASSERT_NULL(list->head);
	TEST_ASSERT_NULL(list->tail);
}

void test_ListSort_SimpleUnsortedIntegersList(void)
{
	int arr[] = {55, 11, 33, 22, 44};

	list = list_create(sizeof(int));

	for (int i = 0; i < sizeof(arr)/sizeof(int); ++i)
		list_push_back(list, &arr[i]);

	void *ret = list_sort(list, (t_list_compare)&compare_int);

	TEST_ASSERT_EQUAL(5, list->len);
	TEST_ASSERT_NOT_NULL(ret);
	TEST_ASSERT_EQUAL_PTR(list, ret);
	TEST_ASSERT_NOT_NULL(list->head);
	TEST_ASSERT_NOT_NULL(list->tail);

	// check list integrity
	const t_list_node	*node;
	const t_list_node	*prev;
	int n;

	node = list->head;
	n = *(int*)LIST_NODE_DATA(node);
	TEST_ASSERT_NULL(node->prev);
	TEST_ASSERT_NOT_NULL(node->next);
	TEST_ASSERT_EQUAL(11, n);

	prev = node;
	node = node->next;
	n = *(int*)LIST_NODE_DATA(node);
	TEST_ASSERT_EQUAL_PTR(prev, node->prev);
	TEST_ASSERT_NOT_NULL(node->next);
	TEST_ASSERT_EQUAL(22, n);

	prev = node;
	node = node->next;
	n = *(int*)LIST_NODE_DATA(node);
	TEST_ASSERT_EQUAL_PTR(prev, node->prev);
	TEST_ASSERT_NOT_NULL(node->next);
	TEST_ASSERT_EQUAL(33, n);

	prev = node;
	node = node->next;
	n = *(int*)LIST_NODE_DATA(node);
	TEST_ASSERT_EQUAL_PTR(prev, node->prev);
	TEST_ASSERT_NOT_NULL(node->next);
	TEST_ASSERT_EQUAL(44, n);

	prev = node;
	node = node->next;
	n = *(int*)LIST_NODE_DATA(node);
	TEST_ASSERT_EQUAL_PTR(prev, node->prev);
	TEST_ASSERT_NULL(node->next);
	TEST_ASSERT_EQUAL(55, n);
}

void test_ListSort_SimpleAlreadySortedIntegersList(void)
{
	int arr[] = {11, 22, 33, 44, 55, 66, 77};

	list = list_create(sizeof(int));

	for (int i = 0; i < sizeof(arr)/sizeof(int); ++i)
		list_push_back(list, &arr[i]);

	void *ret = list_sort(list, (t_list_compare)&compare_int);

	TEST_ASSERT_EQUAL(7, list->len);
	TEST_ASSERT_NOT_NULL(ret);
	TEST_ASSERT_EQUAL_PTR(list, ret);
	TEST_ASSERT_NOT_NULL(list->head);
	TEST_ASSERT_NOT_NULL(list->tail);

	// check list integrity
	const t_list_node	*node;
	const t_list_node	*prev;
	int n;

	node = list->head;
	n = *(int*)LIST_NODE_DATA(node);
	TEST_ASSERT_NULL(node->prev);
	TEST_ASSERT_NOT_NULL(node->next);
	TEST_ASSERT_EQUAL(11, n);

	prev = node;
	node = node->next;
	n = *(int*)LIST_NODE_DATA(node);
	TEST_ASSERT_EQUAL_PTR(prev, node->prev);
	TEST_ASSERT_NOT_NULL(node->next);
	TEST_ASSERT_EQUAL(22, n);

	prev = node;
	node = node->next;
	n = *(int*)LIST_NODE_DATA(node);
	TEST_ASSERT_EQUAL_PTR(prev, node->prev);
	TEST_ASSERT_NOT_NULL(node->next);
	TEST_ASSERT_EQUAL(33, n);

	prev = node;
	node = node->next;
	n = *(int*)LIST_NODE_DATA(node);
	TEST_ASSERT_EQUAL_PTR(prev, node->prev);
	TEST_ASSERT_NOT_NULL(node->next);
	TEST_ASSERT_EQUAL(44, n);

	prev = node;
	node = node->next;
	n = *(int*)LIST_NODE_DATA(node);
	TEST_ASSERT_EQUAL_PTR(prev, node->prev);
	TEST_ASSERT_NOT_NULL(node->next);
	TEST_ASSERT_EQUAL(55, n);

	prev = node;
	node = node->next;
	n = *(int*)LIST_NODE_DATA(node);
	TEST_ASSERT_EQUAL_PTR(prev, node->prev);
	TEST_ASSERT_NOT_NULL(node->next);
	TEST_ASSERT_EQUAL(66, n);

	prev = node;
	node = node->next;
	n = *(int*)LIST_NODE_DATA(node);
	TEST_ASSERT_EQUAL_PTR(prev, node->prev);
	TEST_ASSERT_NULL(node->next);
	TEST_ASSERT_EQUAL(77, n);
}

void test_ListSort_ListWithOnlyOneElement(void)
{
	int arr[] = {11};

	list = list_create(sizeof(int));

	for (int i = 0; i < sizeof(arr)/sizeof(int); ++i)
		list_push_back(list, &arr[i]);

	void *ret = list_sort(list, (t_list_compare)&compare_int);

	TEST_ASSERT_EQUAL(1, list->len);
	TEST_ASSERT_NOT_NULL(ret);
	TEST_ASSERT_EQUAL_PTR(list, ret);
	TEST_ASSERT_NOT_NULL(list->head);
	TEST_ASSERT_NOT_NULL(list->tail);

	// check list integrity
	const t_list_node	*node;
	const t_list_node	*prev;
	int n;

	node = list->head;
	n = *(int*)LIST_NODE_DATA(node);
	TEST_ASSERT_NULL(node->prev);
	TEST_ASSERT_NULL(node->next);
	TEST_ASSERT_EQUAL_PTR(list->head, list->tail);
	TEST_ASSERT_EQUAL(11, n);
}

void test_ListSort_ListWithTwoElementsAlreadySorted(void)
{
	int arr[] = {11, 22};

	list = list_create(sizeof(int));

	for (int i = 0; i < sizeof(arr)/sizeof(int); ++i)
		list_push_back(list, &arr[i]);

	void *ret = list_sort(list, (t_list_compare)&compare_int);

	TEST_ASSERT_EQUAL(2, list->len);
	TEST_ASSERT_NOT_NULL(ret);
	TEST_ASSERT_EQUAL_PTR(list, ret);
	TEST_ASSERT_NOT_NULL(list->head);
	TEST_ASSERT_NOT_NULL(list->tail);

	// check list integrity
	const t_list_node	*node;
	const t_list_node	*prev;
	int n;

	node = list->head;
	n = *(int*)LIST_NODE_DATA(node);
	TEST_ASSERT_NULL(node->prev);
	TEST_ASSERT_NOT_NULL(node->next);
	TEST_ASSERT_EQUAL(11, n);

	prev = node;
	node = node->next;
	n = *(int*)LIST_NODE_DATA(node);
	TEST_ASSERT_EQUAL_PTR(prev, node->prev);
	TEST_ASSERT_NULL(node->next);
	TEST_ASSERT_EQUAL(22, n);
}

void test_ListSort_ListWithTwoElementsUnsorted(void)
{
	int arr[] = {22, 11};

	list = list_create(sizeof(int));

	for (int i = 0; i < sizeof(arr)/sizeof(int); ++i)
		list_push_back(list, &arr[i]);

	void *ret = list_sort(list, (t_list_compare)&compare_int);

	TEST_ASSERT_EQUAL(2, list->len);
	TEST_ASSERT_NOT_NULL(ret);
	TEST_ASSERT_EQUAL_PTR(list, ret);
	TEST_ASSERT_NOT_NULL(list->head);
	TEST_ASSERT_NOT_NULL(list->tail);

	// check list integrity
	const t_list_node	*node;
	const t_list_node	*prev;
	int n;

	node = list->head;
	n = *(int*)LIST_NODE_DATA(node);
	TEST_ASSERT_NULL(node->prev);
	TEST_ASSERT_NOT_NULL(node->next);
	TEST_ASSERT_EQUAL(11, n);

	prev = node;
	node = node->next;
	n = *(int*)LIST_NODE_DATA(node);
	TEST_ASSERT_EQUAL_PTR(prev, node->prev);
	TEST_ASSERT_NULL(node->next);
	TEST_ASSERT_EQUAL(22, n);
}

// Faire un test avec un tableau de 4096 int random
