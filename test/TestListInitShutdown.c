#include "unity.h"
#include "list_42.h"

void test_ListInit_InitWithNormalElemSize(void)
{
	t_list list;
	size_t elem_size = sizeof list;

	void *ret = list_init(&list, elem_size);

	TEST_ASSERT_NOT_NULL(ret);
	TEST_ASSERT_EQUAL_PTR(&list, ret);

	TEST_ASSERT_NOT_NULL(list.pool);
	TEST_ASSERT_NULL(list.head);
	TEST_ASSERT_NULL(list.tail);
	TEST_ASSERT_EQUAL_INT(0, list.len);
	TEST_ASSERT_EQUAL_INT(elem_size, list.elem_size);
}

void test_ListInit_InitWithElemSizeAsOne(void)
{
	t_list list;
	size_t elem_size = 1;

	void *ret = list_init(&list, elem_size);

	TEST_ASSERT_NOT_NULL(ret);
	TEST_ASSERT_EQUAL_PTR(&list, ret);

	TEST_ASSERT_NOT_NULL(list.pool);
	TEST_ASSERT_NULL(list.head);
	TEST_ASSERT_NULL(list.tail);
	TEST_ASSERT_EQUAL_INT(0, list.len);
	TEST_ASSERT_EQUAL_INT(elem_size, list.elem_size);
}

void test_ListInit_InitWithElemSizeAsZero(void)
{
	t_list list;

	void *ret = list_init(&list, 0);

	TEST_ASSERT_NULL(ret);
}

void test_ListShutdown_AllFieldsAreClear(void)
{
	t_list list;

	void *ret = list_init(&list, 16);
	TEST_ASSERT_NOT_NULL(ret);
	TEST_ASSERT_EQUAL_PTR(&list, ret);

	list_shutdown(&list);
	TEST_ASSERT_NULL(list.pool);
	TEST_ASSERT_NULL(list.head);
	TEST_ASSERT_NULL(list.tail);
	TEST_ASSERT_EQUAL_INT(0, list.len);
	TEST_ASSERT_EQUAL_INT(0, list.elem_size);
}
