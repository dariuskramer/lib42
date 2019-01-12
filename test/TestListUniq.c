#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "unity.h"
#include "list_42.h"

static t_list list;

void setUp(void)
{
	void *ret = list_init(&list, sizeof(int));
	TEST_ASSERT_NOT_NULL(ret);
}

void tearDown(void)
{
	list_shutdown(&list);
}

int	compare(int *a, int *b)
{
	return (*a - *b);
}

static void fillList(t_list *list, int *numbers, size_t nlen)
{
	for (size_t i = 0; i < nlen; ++i)
	{
		list_push_back(list, &numbers[i]);
	}
}

static void	checkListIntegrity(const t_list *list, int *numbers, size_t nlen, const char *name)
{
	t_list_node	*node;
	const int	*data;

	TEST_ASSERT_EQUAL_MESSAGE(nlen, list->len, name);

	node = list->head;
	for (size_t i = 0; i < nlen; ++i, node = node->next)
	{
		data = (const int*)LIST_NODE_DATA(node);
		TEST_ASSERT_EQUAL(numbers[i], *data);
	}
	TEST_ASSERT_NULL(node);
}

void test_ListUniqSorted_OnlyOneElement(void)
{
	t_list		*new;
	int			numbers[] = {42};
	size_t		numbers_len = sizeof(numbers) / sizeof(numbers[0]);

	// fill list
	fillList(&list, numbers, numbers_len);

	// create uniq list
	new = list_uniq_sorted(&list, (t_list_compare)&compare);

	// check origin list
	checkListIntegrity(&list, numbers, numbers_len, "origin");

	// check uniq list
	checkListIntegrity(new, numbers, numbers_len, "new");

	list_destroy(new);
}

void test_ListUniqSorted_AllElementsAreTheSame(void)
{
	t_list		*new;
	int			numbers[] = {42, 42, 42};
	size_t		numbers_len = sizeof(numbers) / sizeof(numbers[0]);

	// fill list
	fillList(&list, numbers, numbers_len);

	// create uniq list
	new = list_uniq_sorted(&list, (t_list_compare)&compare);

	// check origin list
	checkListIntegrity(&list, numbers, numbers_len, "origin");

	// check uniq list
	int			numbers2[] = {42};
	checkListIntegrity(new, numbers, 1, "new");

	list_destroy(new);
}

void test_ListUniqSorted_AllElementsAreDifferent(void)
{
	t_list		*new;
	int			numbers[] = {42, 43, 44};
	size_t		numbers_len = sizeof(numbers) / sizeof(numbers[0]);

	// fill list
	fillList(&list, numbers, numbers_len);

	// create uniq list
	new = list_uniq_sorted(&list, (t_list_compare)&compare);

	// check origin list
	checkListIntegrity(&list, numbers, numbers_len, "origin");

	// check uniq list
	checkListIntegrity(new, numbers, numbers_len, "new");

	list_destroy(new);
}

void test_ListUniqSorted_TwoElementsUnique(void)
{
	t_list		*new;
	int			numbers[] = {42, 42};
	size_t		numbers_len = sizeof(numbers) / sizeof(numbers[0]);

	// fill list
	fillList(&list, numbers, numbers_len);

	// create uniq list
	new = list_uniq_sorted(&list, (t_list_compare)&compare);

	// check origin list
	checkListIntegrity(&list, numbers, numbers_len, "origin");

	// check uniq list
	int			numbers2[] = {42};
	checkListIntegrity(new, numbers2, 1, "new");

	list_destroy(new);
}

void test_ListUniqSorted_TwoElementsDifferent(void)
{
	t_list		*new;
	int			numbers[] = {42, 24};
	size_t		numbers_len = sizeof(numbers) / sizeof(numbers[0]);

	// fill list
	fillList(&list, numbers, numbers_len);

	// create uniq list
	new = list_uniq_sorted(&list, (t_list_compare)&compare);

	// check origin list
	checkListIntegrity(&list, numbers, numbers_len, "origin");

	// check uniq list
	checkListIntegrity(new, numbers, numbers_len, "new");

	list_destroy(new);
}

void test_ListUniqSorted_RandomList(void)
{
	t_list		*new;
	int			numbers[] = {1, 2, 3, 4, 4, 4, 5, 5, 6, 7, 7};
	size_t		numbers_len = sizeof(numbers) / sizeof(numbers[0]);

	// fill list
	fillList(&list, numbers, numbers_len);

	// create uniq list
	new = list_uniq_sorted(&list, (t_list_compare)&compare);

	// check origin list
	checkListIntegrity(&list, numbers, numbers_len, "origin");

	// check uniq list
	int			numbers2[] = {1, 2, 3, 4, 5, 6, 7};
	numbers_len = sizeof(numbers2) / sizeof(numbers2[0]);
	checkListIntegrity(new, numbers2, numbers_len, "new");

	list_destroy(new);
}
