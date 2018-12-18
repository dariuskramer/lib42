#include "unity.h"
#include "list_42.h"

static t_list *list;

void test_ListCreate_CreateWithNormalElemSize(void)
{
	size_t elem_size = sizeof list;

	list = list_create(elem_size);
	TEST_ASSERT_NOT_NULL(list);

	TEST_ASSERT_NOT_NULL(list->pool);
	TEST_ASSERT_NULL(list->head);
	TEST_ASSERT_NULL(list->tail);
	TEST_ASSERT_EQUAL_INT(0, list->len);
	TEST_ASSERT_EQUAL_INT(elem_size, list->elem_size);

	list_destroy(list);
}

void test_ListCreate_CreateWithElemSizeAsOne(void)
{
	size_t elem_size = 1;

	list = list_create(elem_size);
	TEST_ASSERT_NOT_NULL(list);

	TEST_ASSERT_NOT_NULL(list->pool);
	TEST_ASSERT_NULL(list->head);
	TEST_ASSERT_NULL(list->tail);
	TEST_ASSERT_EQUAL_INT(0, list->len);
	TEST_ASSERT_EQUAL_INT(elem_size, list->elem_size);

	list_destroy(list);
}

void test_ListCreate_CreateWithElemSizeAsZero(void)
{
	list = list_create(0);
	TEST_ASSERT_NULL(list);
}
