#include "unity.h"
#include "list_42.h"

void test_ListMacro_LIST_NODE_DATA(void)
{
	int a = 42;
	int *pa = &a;

	TEST_ASSERT_EQUAL_PTR(&pa[1], LIST_NODE_DATA(&a));
	TEST_ASSERT_EQUAL_PTR(&pa[1], LIST_NODE_DATA(pa));

	char c[3];
	char *pc = c;
	TEST_ASSERT_EQUAL_PTR(&pc[1], LIST_NODE_DATA(pc));
}
