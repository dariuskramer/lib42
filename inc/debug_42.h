#ifndef DEBUG_42_H
# define DEBUG_42_H

# include <stddef.h>
# include <stdio.h>

/*
** Array
*/
#define DEBUG_ARRAY_PRINT_STR		(0)
#define DEBUG_ARRAY_PRINT_PTR		(1)
#define DEBUG_ARRAY_PRINT_USG		(2)
#define DEBUG_ARRAY_PRINT_SIZET		(3)
#define DEBUG_ARRAY_PRINT_NONE		(4)

#define debug_array_print(a, p)												\
	do {																	\
		printf("array->capacity: %zu\n", (a)->capacity);					\
		printf("array->len: %zu\n", (a)->len);								\
		printf("array->elem_size: %zu\n", (a)->elem_size);					\
		printf("array->data: %p\n", (void*)(a)->data);						\
		switch (p) {														\
			case DEBUG_ARRAY_PRINT_STR:										\
				for (size_t i = 0; i < (a)->len; ++i)						\
					printf("a->data[%zu] => %s\n", i, *(char**)array_get_at(a, i));	\
				break ;														\
																			\
			case DEBUG_ARRAY_PRINT_PTR:										\
			for (size_t i = 0; i < (a)->len; ++i)							\
			printf("a->data[%zu] => %p\n", i, *(void**)array_get_at(a, i));	\
				break ;														\
																			\
			case DEBUG_ARRAY_PRINT_USG:										\
				for (size_t i = 0; i < (a)->len; ++i)						\
					printf("a->data[%zu] => %u\n", i, *(unsigned*)array_get_at(a, i));	\
				break ;														\
																			\
			case DEBUG_ARRAY_PRINT_SIZET:									\
				for (size_t i = 0; i < (a)->len; ++i)						\
					printf("a->data[%zu] => %zu\n", i, *(size_t*)array_get_at(a, i));	\
				break ;														\
																			\
			case DEBUG_ARRAY_PRINT_NONE:									\
				break ;														\
																			\
			default:														\
				for (size_t i = 0; i < (a)->len; ++i)						\
				{															\
					printf("a->data[%zu] => ", i);							\
					(*(void(*)(void*))p)(*(void**)array_get_at(a, i));		\
				}															\
		}																	\
	} while (0);															\

/*
** Print Memory
*/
# define BYTE_PER_BLOCK	2
# define ASCII_PER_LINE	16
# define NB_PRINT_HEX	2 * ASCII_PER_LINE
# define NB_PRINT_SPACE	ASCII_PER_LINE / BYTE_PER_BLOCK
# define NB_COLUMNS		NB_PRINT_HEX + NB_PRINT_SPACE

void	ft_print_memory(const void *addr, size_t size);

#endif
