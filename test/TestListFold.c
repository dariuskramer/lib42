#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "unity.h"
#include "list_42.h"

void checkListIntegrity(t_list *list, const char **expected, size_t len);
void fillList(t_list *list, const char **s, size_t len);

static t_list list;
static char **ret;
void setUp(void)
{
	void *ret = list_init(&list, sizeof(char*));
	TEST_ASSERT_NOT_NULL(ret);
}

void tearDown(void)
{
	list_shutdown(&list);
}

/*
 * String, dynamically allocated
 */
static const char *s[] =
{
	"Hello",
	"world",
	"and",
	"good-bye-afternoon",
	"morning!"
};
static size_t len_s = sizeof s / (sizeof s[0]);

size_t	*wrapper(size_t *len, const char **s)
{
	*len += strlen(*s);
	return (len);
}

void test_ListFoldLeft_StringLength(void)
{
	fillList(&list, s, len_s);

	// Init val
	size_t	init = 0;
	size_t	expected = 0;
	size_t	*len;

	// List fold
	len = list_fold_left(&list, (t_list_fold)&wrapper, &init);

	// Expected
	for (size_t i = 0; i < len_s; ++i) expected += strlen(s[i]);

	// Check list struct
	checkListIntegrity(&list, s, len_s);
	TEST_ASSERT_EQUAL(expected, *len);
	TEST_ASSERT_TRUE(&init == len);
}
