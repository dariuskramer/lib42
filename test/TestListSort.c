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

void test_ListSort_SimpleIntegers(void)
{
	int arr[] = {55, 11, 33, 22, 44};

	list = list_create(sizeof(int));

	printf("arr:");
	for (int i = 0; i < sizeof(arr)/sizeof(int); ++i)
	{
		printf(" %d", arr[i]);
		list_push_back(list, &arr[i]);
	}
	printf("\n");
	TEST_ASSERT_EQUAL(5, list->len);
	TEST_ASSERT_NOT_NULL(list->head);
	TEST_ASSERT_NOT_NULL(list->head->next);
	TEST_ASSERT_NOT_NULL(list->head->next->next);
	TEST_ASSERT_NOT_NULL(list->head->next->next->next);
	TEST_ASSERT_NOT_NULL(list->head->next->next->next->next);

	void *ret = list_sort(list, (t_list_compare)&compare_int);

	TEST_ASSERT_EQUAL(5, list->len);
	TEST_ASSERT_NOT_NULL(ret);
	TEST_ASSERT_EQUAL_PTR(list, ret);

	int n;

	n = *(int*)list_get_at(list, 0);
	TEST_ASSERT_EQUAL(11, n);
	n = *(int*)list_get_at(list, 1);
	TEST_ASSERT_EQUAL(22, n);
	n = *(int*)list_get_at(list, 2);
	TEST_ASSERT_EQUAL(33, n);
	n = *(int*)list_get_at(list, 3);
	TEST_ASSERT_EQUAL(44, n);
	n = *(int*)list_get_at(list, 4);
	TEST_ASSERT_EQUAL(55, n);
}
