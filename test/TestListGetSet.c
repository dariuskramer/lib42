#include <string.h>
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

void test_ListGetFirst_WithEmptyList(void)
{
	void *ret = list_get_first(&list);
	TEST_ASSERT_NULL(ret);
}

void test_ListGetFirst_WithSimpleList(void)
{
	fillList(&list, s, len_s);

	char **ret = list_get_first(&list);
	TEST_ASSERT_EQUAL_STRING(s[0], *ret);

	// 0 -> 1 -> 2 -> 3 -> 4
	checkListIntegrity(&list, s, len_s);
}

void test_ListGetLast_WithEmptyList(void)
{
	void *ret = list_get_last(&list);
	TEST_ASSERT_NULL(ret);
}

void test_ListGetLast_WithSimpleList(void)
{
	fillList(&list, s, len_s);

	char **ret = list_get_last(&list);
	TEST_ASSERT_EQUAL_STRING(s[4], *ret);

	// 0 -> 1 -> 2 -> 3 -> 4
	checkListIntegrity(&list, s, len_s);
}

void test_ListGetAt_GetFirstWithEmptyList(void)
{
	void *ret = list_get_at(&list, 0);
	TEST_ASSERT_NULL(ret);
}

void test_ListGetAt_GetFirstWithSimpleList(void)
{
	fillList(&list, s, len_s);

	char **ret = list_get_at(&list, 0);
	TEST_ASSERT_EQUAL_STRING(s[0], *ret);

	// hello -> world -> and -> good -> morning
	checkListIntegrity(&list, s, len_s);
}

void test_ListGetAt_GetLastWithSimpleList(void)
{
	fillList(&list, s, len_s);

	char **ret = list_get_at(&list, list.len - 1);
	TEST_ASSERT_EQUAL_STRING(s[4], *ret);

	// hello -> world -> and -> good -> morning
	checkListIntegrity(&list, s, len_s);
}

void test_ListGetAt_GetEachWithSimpleList(void)
{
	fillList(&list, s, len_s);

	for (size_t i = 0; i < list.len; ++i)
	{
		char **ret = list_get_at(&list, i);
		TEST_ASSERT_EQUAL_STRING(s[i], *ret);
	}

	// hello -> world -> and -> good -> morning
	checkListIntegrity(&list, s, len_s);
}

void test_ListSetAt_SetFirstWithEmptyList(void)
{
	const char *str = "first";

	void *ret = list_set_at(&list, 0, &str);
	TEST_ASSERT_NULL(ret);

	ret = list_set_at(&list, 1, &str);
	TEST_ASSERT_NULL(ret);
}
	
void test_ListSetAt_SetFirstWithSimpleList(void)
{
	const char *str = "first";
	fillList(&list, s, len_s);

	char **ret = list_set_at(&list, 0, &str);
	TEST_ASSERT_EQUAL_PTR(str, *ret);
	TEST_ASSERT_EQUAL_STRING(str, *ret);

	const char *arr[len_s];
	memcpy(arr, s, sizeof s);
	arr[0] = str;

	// first -> world -> and -> good -> morning
	checkListIntegrity(&list, arr, 5);
}

void test_ListSetAt_SetLastWithSimpleList(void)
{
	const char *str = "last";
	fillList(&list, s, len_s);

	char **ret = list_set_at(&list, list.len - 1, &str);
	TEST_ASSERT_EQUAL_PTR(str, *ret);
	TEST_ASSERT_EQUAL_STRING(str, *ret);

	const char *arr[len_s];
	memcpy(arr, s, sizeof s);
	arr[4] = str;

	// hello -> world -> and -> good -> last
	checkListIntegrity(&list, arr, 5);
}

void test_ListSetAt_SetMiddleWithSimpleList(void)
{
	const char *str = "middle";
	fillList(&list, s, len_s);

	char **ret = list_set_at(&list, 2, &str);
	TEST_ASSERT_EQUAL_PTR(str, *ret);
	TEST_ASSERT_EQUAL_STRING(str, *ret);

	const char *arr[len_s];
	memcpy(arr, s, sizeof s);
	arr[2] = str;

	// hello -> world -> middle -> good -> morning
	checkListIntegrity(&list, arr, 5);
}

void test_ListSetAt_SetOnePastLast(void)
{
	const char *str = "past last";
	fillList(&list, s, len_s);

	void *ret = list_set_at(&list, list.len, &str);
	TEST_ASSERT_NULL(ret);
}

void test_ListSetAt_SetAllWithFirst(void)
{
	const char *str = "all-the-same";
	fillList(&list, s, len_s);

	for (size_t i = 0; i < list.len; ++i)
	{
		char **ret = list_set_at(&list, i, &str);
		TEST_ASSERT_EQUAL_PTR(str, *ret);
		TEST_ASSERT_EQUAL_STRING(str, *ret);
	}

	const char *arr[len_s];
	arr[0] = str;
	arr[1] = str;
	arr[2] = str;
	arr[3] = str;
	arr[4] = str;

	// all-the-same all-the-same all-the-same all-the-same all-the-same
	checkListIntegrity(&list, arr, 5);
}
