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

void test_ListInsertAt_WithEmptyList(void)
{
	const char *str = "first";

	void *ret = list_insert_at(&list, 0, &str);
	TEST_ASSERT_NULL(ret);
}

void test_ListInsertAt_FirstPosition(void)
{
	const char *str = "first";
	const char *str2 = "more first";
	fillList(&list, s, len_s);

	char **ret = list_insert_at(&list, 0, &str);
	TEST_ASSERT_EQUAL_PTR(str, *ret);
	TEST_ASSERT_EQUAL_STRING(str, *ret);

	ret = list_insert_at(&list, 0, &str2);
	TEST_ASSERT_EQUAL_PTR(str2, *ret);
	TEST_ASSERT_EQUAL_STRING(str2, *ret);

	const char *arr[7];
	arr[0] = str2;
	arr[1] = str;
	memcpy(&arr[2], s, sizeof s);

	// more first -> first -> hello -> world -> and -> good -> morning
	checkListIntegrity(&list, arr, 7);
}

void test_ListInsertAt_MiddlePosition(void)
{
	const char *str = "second middle";
	const char *str2 = "middle";
	fillList(&list, s, len_s);

	char **ret = list_insert_at(&list, 2, &str);
	TEST_ASSERT_EQUAL_PTR(str, *ret);
	TEST_ASSERT_EQUAL_STRING(str, *ret);

	ret = list_insert_at(&list, 2, &str2);
	TEST_ASSERT_EQUAL_PTR(str2, *ret);
	TEST_ASSERT_EQUAL_STRING(str2, *ret);

	const char *arr[7];
	arr[0] = s[0];
	arr[1] = s[1];
	arr[2] = str2;
	arr[3] = str;
	arr[4] = s[2];
	arr[5] = s[3];
	arr[6] = s[4];

	// hello -> world -> middle -> second middle -> and -> good -> morning
	checkListIntegrity(&list, arr, 7);
}

void test_ListInsertAt_LastPosition(void)
{
	const char *str = "last";
	const char *str2 = "true last";
	fillList(&list, s, len_s);

	char **ret = list_insert_at(&list, list.len - 1, &str);
	TEST_ASSERT_EQUAL_PTR(str, *ret);
	TEST_ASSERT_EQUAL_STRING(str, *ret);

	ret = list_insert_at(&list, list.len - 1, &str2);
	TEST_ASSERT_EQUAL_PTR(str2, *ret);
	TEST_ASSERT_EQUAL_STRING(str2, *ret);

	const char *arr[7];
	arr[0] = s[0];
	arr[1] = s[1];
	arr[2] = s[2];
	arr[3] = s[3];
	arr[4] = str;
	arr[5] = str2;
	arr[6] = s[4];

	// hello -> world -> and -> good -> last -> true last -> morning
	checkListIntegrity(&list, arr, 7);
}

void test_ListInsertAt_OnePastLastPosition(void)
{
	const char *str = "one past last";
	fillList(&list, s, len_s);

	char **ret = list_insert_at(&list, list.len, &str);
	TEST_ASSERT_NULL(ret);
}
