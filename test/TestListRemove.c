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

void test_ListRemove_FromEmptyList(void)
{
	void *ret = list_remove_at(&list, 0, NULL);
	TEST_ASSERT_NULL(ret);

	void *backup = (void*)~0;
	ret = list_remove_at(&list, 0, &backup);
	TEST_ASSERT_NULL(ret);
	TEST_ASSERT_EQUAL_PTR((void*)~0, backup);

	TEST_ASSERT_EQUAL(0, list.len);
	TEST_ASSERT_NULL(list.head);
	TEST_ASSERT_NULL(list.tail);
}

void test_ListRemove_LastElementOfList(void)
{
	const char *str = "only one";
	list_push_front(&list, &str);

	void *ret = list_remove_at(&list, 0, NULL);
	TEST_ASSERT_EQUAL_PTR(&list, ret);
	TEST_ASSERT_EQUAL(0, list.len);
	TEST_ASSERT_NULL(list.head);
	TEST_ASSERT_NULL(list.tail);

	list_push_front(&list, &str);

	char *backup;
	ret = list_remove_at(&list, 0, &backup);
	TEST_ASSERT_EQUAL_PTR(&list, ret);
	TEST_ASSERT_EQUAL(0, list.len);
	TEST_ASSERT_NULL(list.head);
	TEST_ASSERT_NULL(list.tail);
	TEST_ASSERT_EQUAL_PTR(str, backup);
}

void test_ListRemove_FirstElementFromList(void)
{
	fillList(&list, s, len_s);

	void *ret = list_remove_at(&list, 0, NULL);
	TEST_ASSERT_EQUAL_PTR(&list, ret);

	const char *arr[4];
	arr[0] = s[1];
	arr[1] = s[2];
	arr[2] = s[3];
	arr[3] = s[4];

	// world -> and -> good -> morning
	checkListIntegrity(&list, arr, 4);

	list_push_front(&list, &s[0]);
	checkListIntegrity(&list, s, len_s);

	void *backup;
	ret = list_remove_at(&list, 0, &backup);
	TEST_ASSERT_EQUAL_PTR(&list, ret);
	TEST_ASSERT_EQUAL(4, list.len);
	TEST_ASSERT_NOT_NULL(list.head);
	TEST_ASSERT_NOT_NULL(list.tail);
	TEST_ASSERT_EQUAL_PTR(s[0], backup);

	// world -> and -> good -> morning
	checkListIntegrity(&list, arr, 4);
}

void test_ListRemove_LastElementFromList(void)
{
	fillList(&list, s, len_s);

	void *ret = list_remove_at(&list, list.len-1, NULL);
	TEST_ASSERT_EQUAL_PTR(&list, ret);

	const char *arr[4];
	arr[0] = s[0];
	arr[1] = s[1];
	arr[2] = s[2];
	arr[3] = s[3];

	// hello -> world -> and -> good
	checkListIntegrity(&list, arr, 4);

	list_push_back(&list, &s[4]);
	checkListIntegrity(&list, s, len_s);

	void *backup;
	ret = list_remove_at(&list, list.len-1, &backup);
	TEST_ASSERT_EQUAL_PTR(&list, ret);
	TEST_ASSERT_EQUAL(4, list.len);
	TEST_ASSERT_NOT_NULL(list.head);
	TEST_ASSERT_NOT_NULL(list.tail);
	TEST_ASSERT_EQUAL_PTR(s[4], backup);

	// hello -> world -> and -> good
	checkListIntegrity(&list, arr, 4);
}

void test_ListRemove_MiddleElementFromList(void)
{
	fillList(&list, s, len_s);

	void *ret = list_remove_at(&list, 2, NULL);
	TEST_ASSERT_EQUAL_PTR(&list, ret);

	const char *arr[4];
	arr[0] = s[0];
	arr[1] = s[1];
	arr[2] = s[3];
	arr[3] = s[4];

	// hello -> world -> good -> morning
	checkListIntegrity(&list, arr, 4);

	list_insert_at(&list, 2, &s[2]);
	checkListIntegrity(&list, s, len_s);

	void *backup;
	ret = list_remove_at(&list, 2, &backup);
	TEST_ASSERT_EQUAL_PTR(&list, ret);
	TEST_ASSERT_EQUAL(4, list.len);
	TEST_ASSERT_NOT_NULL(list.head);
	TEST_ASSERT_NOT_NULL(list.tail);
	TEST_ASSERT_EQUAL_PTR(s[2], backup);

	// hello -> world -> good -> morning
	checkListIntegrity(&list, arr, 4);
}

void test_ListRemove_OnePastTheLastElementFromList(void)
{
	fillList(&list, s, len_s);

	void *ret = list_remove_at(&list, list.len, NULL);
	TEST_ASSERT_NULL(ret);
	checkListIntegrity(&list, s, len_s);

	void *backup = (void*)~0;
	ret = list_remove_at(&list, list.len, &backup);
	TEST_ASSERT_NULL(ret);
	TEST_ASSERT_EQUAL_PTR((void*)~0, backup);
	checkListIntegrity(&list, s, len_s);
}

void test_ListRemove_AllElement(void)
{
	void *backup;
	void *ret;
	size_t idx;
	const char *arr[5];

	// hello => world => and => good => morning
	fillList(&list, s, len_s);

	ret = list_remove_at(&list, list.len / 2, &backup);
	TEST_ASSERT_EQUAL_PTR(&list, ret);
	TEST_ASSERT_EQUAL(4, list.len);
	TEST_ASSERT_EQUAL_PTR(s[2], backup);
	arr[0] = s[0];
	arr[1] = s[1];
	arr[2] = s[3];
	arr[3] = s[4];

	// hello -> world -> good -> morning
	checkListIntegrity(&list, arr, list.len);

	ret = list_remove_at(&list, list.len / 2, &backup);
	TEST_ASSERT_EQUAL_PTR(&list, ret);
	TEST_ASSERT_EQUAL(3, list.len);
	TEST_ASSERT_EQUAL_PTR(s[3], backup);
	arr[0] = s[0];
	arr[1] = s[1];
	arr[2] = s[4];

	// hello -> world -> morning
	checkListIntegrity(&list, arr, list.len);

	ret = list_remove_at(&list, list.len / 2, &backup);
	TEST_ASSERT_EQUAL_PTR(&list, ret);
	TEST_ASSERT_EQUAL(2, list.len);
	TEST_ASSERT_EQUAL_PTR(s[1], backup);
	arr[0] = s[0];
	arr[1] = s[4];

	// hello -> morning
	checkListIntegrity(&list, arr, list.len);

	ret = list_remove_at(&list, list.len / 2, &backup);
	TEST_ASSERT_EQUAL_PTR(&list, ret);
	TEST_ASSERT_EQUAL(1, list.len);
	TEST_ASSERT_EQUAL_PTR(s[4], backup);
	arr[0] = s[0];

	// hello
	checkListIntegrity(&list, arr, list.len);

	ret = list_remove_at(&list, list.len / 2, &backup);
	TEST_ASSERT_EQUAL_PTR(&list, ret);
	TEST_ASSERT_EQUAL(0, list.len);
	TEST_ASSERT_EQUAL_PTR(s[0], backup);
	TEST_ASSERT_NULL(list.head);
	TEST_ASSERT_NULL(list.tail);

	ret = list_remove_at(&list, list.len / 2, &backup);
	TEST_ASSERT_NULL(ret);
	TEST_ASSERT_EQUAL(0, list.len);
	TEST_ASSERT_NULL(list.head);
	TEST_ASSERT_NULL(list.tail);
}
