#include "unity.h"
#include "list_42.h"

void checkListIntegrity(t_list *list, const char **expected, size_t len);
void fillList(t_list *list, const char **s, size_t len);

static char errmsg[512];
static t_list list;
static t_list_node *node;
static char **ret;
static char **data;
static const char *s[] =
{
	"Hello",
	"world",
	"and",
	"good",
	"morning!"
};
static size_t len_s = sizeof s / (sizeof s[0]);

void setUp(void)
{
	void *ret = list_init(&list, sizeof(char*));
	TEST_ASSERT_NOT_NULL(ret);
}

void tearDown(void)
{
	list_shutdown(&list);
	data = NULL;
}

void test_ListPushFront_PushOnlyOneElement(void)
{
	ret = list_push_front(&list, &s[0]);
	TEST_ASSERT_TRUE(s[0] != (char*)ret);
	TEST_ASSERT_EQUAL_STRING(s[0], *ret);
	TEST_ASSERT_EQUAL(1, list.len);

	// head
	data = (char**)LIST_NODE_DATA(list.head);
	TEST_ASSERT_EQUAL_PTR(ret, data);
	TEST_ASSERT_EQUAL_STRING(s[0], *data);
	TEST_ASSERT_NULL(list.head->next);
	TEST_ASSERT_NULL(list.head->prev);

	// tail
	data = (char**)LIST_NODE_DATA(list.tail);
	TEST_ASSERT_EQUAL_PTR(ret, data);
	TEST_ASSERT_EQUAL_STRING(s[0], *data);
	TEST_ASSERT_NULL(list.tail->next);
	TEST_ASSERT_NULL(list.tail->prev);
}

void test_ListPushFront_PushAllElement(void)
{
	for (size_t i = 0; i < len_s; ++i)
	{
		const char *str = s[i];
		ret = list_push_front(&list, &str);
		TEST_ASSERT_TRUE(str != (char*)ret);
		TEST_ASSERT_EQUAL_STRING(str, *ret);
		TEST_ASSERT_EQUAL(i + 1, list.len);
	}

	// 4 -> 3 -> 2 -> 1 -> 0
	const char *expected[] = {s[4], s[3], s[2], s[1], s[0]};
	checkListIntegrity(&list, expected, 5);
}

void test_ListPushBack_PushOnlyOneElement(void)
{
	ret = list_push_back(&list, &s[0]);
	TEST_ASSERT_TRUE(s[0] != (char*)ret);
	TEST_ASSERT_EQUAL_STRING(s[0], *ret);
	TEST_ASSERT_EQUAL(1, list.len);

	// head
	data = (char**)LIST_NODE_DATA(list.head);
	TEST_ASSERT_EQUAL_PTR(ret, data);
	TEST_ASSERT_EQUAL_STRING(s[0], *data);
	TEST_ASSERT_NULL(list.head->next);

	// tail
	data = (char**)LIST_NODE_DATA(list.tail);
	TEST_ASSERT_EQUAL_PTR(ret, data);
	TEST_ASSERT_EQUAL_STRING(s[0], *data);
	TEST_ASSERT_NULL(list.tail->next);
}

void test_ListPushBack_PushAllElement(void)
{
	fillList(&list, s, len_s);

	// 0 -> 1 -> 2 -> 3 -> 4
	checkListIntegrity(&list, s, len_s);
}

void test_ListPushFrontAndBack_PushAllElementAlternatively(void)
{
	// good Hello morning and world
	// 3 -> 0 -> 4 -> 2 -> 1

	const char *str = s[4];
	ret = list_push_front(&list, &str);
	TEST_ASSERT_TRUE(str != (char*)ret);
	TEST_ASSERT_EQUAL_STRING(str, *ret);
	TEST_ASSERT_EQUAL(1, list.len);

	str = s[2];
	ret = list_push_back(&list, &str);
	TEST_ASSERT_TRUE(str != (char*)ret);
	TEST_ASSERT_EQUAL_STRING(str, *ret);
	TEST_ASSERT_EQUAL(2, list.len);

	str = s[0];
	ret = list_push_front(&list, &str);
	TEST_ASSERT_TRUE(str != (char*)ret);
	TEST_ASSERT_EQUAL_STRING(str, *ret);
	TEST_ASSERT_EQUAL(3, list.len);

	str = s[1];
	ret = list_push_back(&list, &str);
	TEST_ASSERT_TRUE(str != (char*)ret);
	TEST_ASSERT_EQUAL_STRING(str, *ret);
	TEST_ASSERT_EQUAL(4, list.len);

	str = s[3];
	ret = list_push_front(&list, &str);
	TEST_ASSERT_TRUE(str != (char*)ret);
	TEST_ASSERT_EQUAL_STRING(str, *ret);
	TEST_ASSERT_EQUAL(5, list.len);


	// 3 -> 0 -> 4 -> 2 -> 1
	const char *expected[] = {s[3], s[0], s[4], s[2], s[1]};
	checkListIntegrity(&list, expected, 5);
}

void test_ListPopFront_PopEveryElementOneByOne(void)
{
	t_list *same_list;
	char *elem;

	fillList(&list, s, len_s);

	// 0 -> 1 -> 2 -> 3 -> 4
	same_list = list_pop_front(&list, &elem);
	// 1 -> 2 -> 3 -> 4
	TEST_ASSERT_EQUAL_PTR(&list, same_list);
	TEST_ASSERT_NULL(list.head->prev);
	TEST_ASSERT_EQUAL_STRING(s[0], elem);
	TEST_ASSERT_EQUAL(4, list.len);
	checkListIntegrity(&list, &s[1], 4);

	// 1 -> 2 -> 3 -> 4
	same_list = list_pop_front(&list, &elem);
	// 2 -> 3 -> 4
	TEST_ASSERT_EQUAL_PTR(&list, same_list);
	TEST_ASSERT_NULL(list.head->prev);
	TEST_ASSERT_EQUAL_STRING(s[1], elem);
	TEST_ASSERT_EQUAL(3, list.len);
	checkListIntegrity(&list, &s[2], 3);

	// 2 -> 3 -> 4
	same_list = list_pop_front(&list, &elem);
	// 3 -> 4
	TEST_ASSERT_EQUAL_PTR(&list, same_list);
	TEST_ASSERT_NULL(list.head->prev);
	TEST_ASSERT_EQUAL_STRING(s[2], elem);
	TEST_ASSERT_EQUAL(2, list.len);
	checkListIntegrity(&list, &s[3], 2);

	// 3 -> 4
	same_list = list_pop_front(&list, &elem);
	// 4
	TEST_ASSERT_EQUAL_PTR(&list, same_list);
	TEST_ASSERT_NULL(list.head->prev);
	TEST_ASSERT_EQUAL_STRING(s[3], elem);
	TEST_ASSERT_EQUAL(1, list.len);
	checkListIntegrity(&list, &s[4], 1);

	// 4
	same_list = list_pop_front(&list, &elem);
	// [empty]
	TEST_ASSERT_EQUAL_PTR(&list, same_list);
	TEST_ASSERT_NULL(list.head);
	TEST_ASSERT_NULL(list.tail);
	TEST_ASSERT_EQUAL_STRING(s[4], elem);
	TEST_ASSERT_EQUAL(0, list.len);
}

void test_ListPopBack_PopEveryElementOneByOne(void)
{
	t_list *same_list;
	char *elem;

	fillList(&list, s, len_s);

	// 0 -> 1 -> 2 -> 3 -> 4
	same_list = list_pop_back(&list, &elem);
	// 0 -> 1 -> 2 -> 3
	TEST_ASSERT_EQUAL_PTR(&list, same_list);
	TEST_ASSERT_NULL(list.tail->next);
	TEST_ASSERT_EQUAL_STRING(s[4], elem);
	TEST_ASSERT_EQUAL(4, list.len);
	checkListIntegrity(&list, s, 4);

	// 0 -> 1 -> 2 -> 3
	same_list = list_pop_back(&list, &elem);
	// 0 -> 1 -> 2
	TEST_ASSERT_EQUAL_PTR(&list, same_list);
	TEST_ASSERT_NULL(list.tail->next);
	TEST_ASSERT_EQUAL_STRING(s[3], elem);
	TEST_ASSERT_EQUAL(3, list.len);
	checkListIntegrity(&list, s, 3);

	// 0 -> 1 -> 2
	same_list = list_pop_back(&list, &elem);
	// 0 -> 1
	TEST_ASSERT_EQUAL_PTR(&list, same_list);
	TEST_ASSERT_NULL(list.tail->next);
	TEST_ASSERT_EQUAL_STRING(s[2], elem);
	TEST_ASSERT_EQUAL(2, list.len);
	checkListIntegrity(&list, s, 2);

	// 0 -> 1
	same_list = list_pop_back(&list, &elem);
	// 0
	TEST_ASSERT_EQUAL_PTR(&list, same_list);
	TEST_ASSERT_NULL(list.tail->next);
	TEST_ASSERT_EQUAL_STRING(s[1], elem);
	TEST_ASSERT_EQUAL(1, list.len);
	checkListIntegrity(&list, s, 1);

	// 0
	same_list = list_pop_back(&list, &elem);
	// [empty]
	TEST_ASSERT_EQUAL_PTR(&list, same_list);
	TEST_ASSERT_NULL(list.head);
	TEST_ASSERT_NULL(list.tail);
	TEST_ASSERT_EQUAL_STRING(s[0], elem);
	TEST_ASSERT_EQUAL(0, list.len);
}

void test_ListPopFrontAndBack_PopEveryElementOneByOne(void)
{
	t_list *same_list;
	char *elem;

	fillList(&list, s, len_s);

	// 0 -> 1 -> 2 -> 3 -> 4
	same_list = list_pop_front(&list, &elem);
	// 1 -> 2 -> 3 -> 4
	TEST_ASSERT_EQUAL_PTR(&list, same_list);
	TEST_ASSERT_NULL(list.tail->next);
	TEST_ASSERT_NULL(list.head->prev);
	TEST_ASSERT_EQUAL_STRING(s[0], elem);
	TEST_ASSERT_EQUAL(4, list.len);
	checkListIntegrity(&list, &s[1], 4);

	// 1 -> 2 -> 3 -> 4
	same_list = list_pop_back(&list, &elem);
	// 1 -> 2 -> 3
	TEST_ASSERT_EQUAL_PTR(&list, same_list);
	TEST_ASSERT_NULL(list.tail->next);
	TEST_ASSERT_NULL(list.head->prev);
	TEST_ASSERT_EQUAL_STRING(s[4], elem);
	TEST_ASSERT_EQUAL(3, list.len);
	checkListIntegrity(&list, &s[1], 3);

	// 1 -> 2 -> 3
	same_list = list_pop_front(&list, &elem);
	// 2 -> 3
	TEST_ASSERT_EQUAL_PTR(&list, same_list);
	TEST_ASSERT_NULL(list.tail->next);
	TEST_ASSERT_NULL(list.head->prev);
	TEST_ASSERT_EQUAL_STRING(s[1], elem);
	TEST_ASSERT_EQUAL(2, list.len);
	checkListIntegrity(&list, &s[2], 2);

	// 2 -> 3
	same_list = list_pop_back(&list, &elem);
	// 2
	TEST_ASSERT_EQUAL_PTR(&list, same_list);
	TEST_ASSERT_NULL(list.tail->next);
	TEST_ASSERT_NULL(list.head->prev);
	TEST_ASSERT_EQUAL_STRING(s[3], elem);
	TEST_ASSERT_EQUAL(1, list.len);
	checkListIntegrity(&list, &s[2], 1);

	// 2
	same_list = list_pop_front(&list, &elem);
	// [empty]
	TEST_ASSERT_EQUAL_PTR(&list, same_list);
	TEST_ASSERT_NULL(list.head);
	TEST_ASSERT_NULL(list.tail);
	TEST_ASSERT_EQUAL_STRING(s[2], elem);
	TEST_ASSERT_EQUAL(0, list.len);
}
