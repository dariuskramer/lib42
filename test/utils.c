#include "unity.h"
#include "list_42.h"

void checkListIntegrity(t_list *list, const char **expected, size_t len)
{
	char **data;
	char errmsg[512];

	t_list_node *current = list->head;

	TEST_ASSERT_EQUAL_INT(len, list->len);
	for (size_t i = 0; i < len; ++i, current = current->next)
	{
		sprintf(errmsg, "Loop counter: %zu", i);

		// current
		data = (char**)LIST_NODE_DATA(current);
		TEST_ASSERT_EQUAL_STRING(expected[i], *data);

		// prev
		if (i > 0)
		{
			data = (char**)LIST_NODE_DATA(current->prev);
			TEST_ASSERT_EQUAL_STRING(expected[i - 1], *data);
		}
		else
			TEST_ASSERT_NULL(current->prev);

		// next
		if (i < len - 1)
		{
			data = (char**)LIST_NODE_DATA(current->next);
			TEST_ASSERT_EQUAL_STRING_MESSAGE(expected[i + 1], *data, errmsg);
		}
		else
		{
			TEST_ASSERT_NULL_MESSAGE(current->next, errmsg);
		}
	}
	TEST_ASSERT_NULL(current);
}

void fillList(t_list *list, const char **s, size_t len)
{
	char **ret;

	for (size_t i = 0; i < len; ++i)
	{
		const char *str = s[i];
		ret = list_push_back(list, &str);
		TEST_ASSERT_TRUE(str != (char*)ret);
		TEST_ASSERT_EQUAL_STRING(str, *ret);
		TEST_ASSERT_EQUAL(i + 1, list->len);
	}
	checkListIntegrity(list, s, len);
	TEST_ASSERT_EQUAL(len, list->len);
}
