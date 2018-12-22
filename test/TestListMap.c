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

char *string_upper(const char *arg)
{
	size_t	len = strlen(arg);
	char	*str = malloc(len + 1);

	for (size_t i = 0; i < len; ++i)
	{
		str[i] = toupper(arg[i]);
	}

	str[len] = '\0';
	return (str);
}

char *ptr_wrap;
char **wrapper_string_upper(const char **arg)
{
	ptr_wrap = string_upper(*arg);
	return (&ptr_wrap);
}

void test_ListMap_UpperAllStrings(void)
{
	fillList(&list, s, len_s);

	// Create mapped list
	t_list	*new_list;
	new_list = list_map(&list, (list_map_func)&wrapper_string_upper, sizeof(char*));

	// Check list struct
	checkListIntegrity(&list, s, len_s);
	TEST_ASSERT_NOT_NULL(new_list);
	TEST_ASSERT(new_list != &list);
	TEST_ASSERT_EQUAL(list.len, new_list->len);
	TEST_ASSERT_EQUAL(8, new_list->elem_size);

	// Check list content
	char *str;
	str = *(char**)LIST_NODE_DATA(new_list->head);
	TEST_ASSERT_EQUAL_STRING("HELLO", str);
	free(str);

	str = *(char**)LIST_NODE_DATA(new_list->head->next);
	TEST_ASSERT_EQUAL_STRING("WORLD", str);
	free(str);

	str = *(char**)LIST_NODE_DATA(new_list->head->next->next);
	TEST_ASSERT_EQUAL_STRING("AND", str);
	free(str);

	str = *(char**)LIST_NODE_DATA(new_list->head->next->next->next);
	TEST_ASSERT_EQUAL_STRING("GOOD-BYE-AFTERNOON", str);
	free(str);

	str = *(char**)LIST_NODE_DATA(new_list->head->next->next->next->next);
	TEST_ASSERT_EQUAL_STRING("MORNING!", str);
	free(str);

	TEST_ASSERT_NULL(new_list->head->next->next->next->next->next);

	// cleanup
	list_destroy(new_list);
}


/*
 * Struct, not dynamically allocated
 */
struct s_dumb
{
	char *name;
	long count;
	void *next;
};
static const struct	s_dumb	dumbs[] = {
	{"bli", 1, NULL},
	{"tom sawyer le fou", 2, (void*)0xdeadbeef},
	{"la fin si proche", 3, (void*)0xcafecafe},
};
static struct s_dumb		used_for_test;

struct s_dumb	*convert(const struct s_dumb *dumb)
{
	used_for_test.name = string_upper(dumb->name);
	used_for_test.count = dumb->count * 10;
	used_for_test.next = dumb->next;
	return (&used_for_test);
}

void test_ListMap_ConvertDumbStruct(void)
{
	// Create initial list
	t_list			*old_list;
	old_list = list_create(sizeof(struct s_dumb));
	TEST_ASSERT_NOT_NULL(old_list);
	list_push_back(old_list, &dumbs[0]);
	list_push_back(old_list, &dumbs[1]);
	list_push_back(old_list, &dumbs[2]);
	TEST_ASSERT_EQUAL_INT(3, old_list->len);
	TEST_ASSERT_EQUAL_INT(24, old_list->elem_size);

	// Check initial list
	struct s_dumb	*p;
	t_list_node		*node;
	node = old_list->head;
	for (size_t i = 0; i < old_list->len; ++i, node = node->next)
	{
		p = LIST_NODE_DATA(node);
		TEST_ASSERT_EQUAL_STRING(dumbs[i].name, p->name);
		TEST_ASSERT_EQUAL(dumbs[i].count, p->count);
		TEST_ASSERT_TRUE(dumbs[i].next == p->next);
		TEST_ASSERT_TRUE(&dumbs[i] != p);
	}


	// Create mapped list
	t_list	*new_list;
	new_list = list_map(old_list, (list_map_func)&convert, sizeof(struct s_dumb));

	// Check list struct
	TEST_ASSERT_NOT_NULL(new_list);
	TEST_ASSERT(new_list != old_list);
	TEST_ASSERT_EQUAL(old_list->len, new_list->len);
	TEST_ASSERT_EQUAL(3, new_list->len);
	TEST_ASSERT_EQUAL(24, new_list->elem_size);

	// Check list content
	p = LIST_NODE_DATA(new_list->head);
	TEST_ASSERT_EQUAL_STRING("BLI", p->name);
	TEST_ASSERT_EQUAL(10, p->count);
	TEST_ASSERT_TRUE(NULL == p->next);
	free(p->name);

	p = LIST_NODE_DATA(new_list->head->next);
	TEST_ASSERT_EQUAL_STRING("TOM SAWYER LE FOU", p->name);
	TEST_ASSERT_EQUAL(20, p->count);
	TEST_ASSERT_TRUE((void*)0xdeadbeef == p->next);
	free(p->name);

	p = LIST_NODE_DATA(new_list->head->next->next);
	TEST_ASSERT_EQUAL_STRING("LA FIN SI PROCHE", p->name);
	TEST_ASSERT_EQUAL(30, p->count);
	TEST_ASSERT_TRUE((void*)0xcafecafe == p->next);
	free(p->name);

	TEST_ASSERT_NULL(new_list->head->next->next->next);

	// Cleanup
	list_destroy(old_list);
	list_destroy(new_list);
}
