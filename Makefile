NAME = lib42.a
CC ?= clang
CFLAGS = -Wall -Werror -Wextra
CFLAGS += -std=c11 -pedantic-errors
CFLAGS += -fno-strict-aliasing

# Debug
ifeq ($(DEBUG),yes)
	CFLAGS += -g3 -O0 -fno-inline
endif

# Profile
ifeq ($(PROF),yes)
	CFLAGS += -pg
endif

# Opti
ifeq ($(PROD),yes)
	CFLAGS += -O2
endif

# Sanitize
ifeq ($(SAN),yes)
	LDFLAGS += -fsanitize=address
	CFLAGS += -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
endif

# Error
SRC_SUBDIR += error
SOURCES += errors.c

# Pool
SRC_SUBDIR += pool
SOURCES += pool_create_acquire.c
SOURCES += pool_destroy_release.c

# Memory
SRC_SUBDIR += memory
SOURCES += next_power.c
SOURCES += ft_malloc_or_die.c
SOURCES += ft_memset.c
SOURCES += ft_memcpy.c
SOURCES += ft_memccpy.c
SOURCES += ft_memmove.c
SOURCES += ft_memcmp.c
SOURCES += ft_realloc.c
ifeq ($(SAN),yes)
	SOURCES += ft_memchr_sanitize.c
else
	SOURCES += ft_memchr.c
endif

# Str
SRC_SUBDIR += str
SOURCES += ft_strcmp.c
SOURCES += ft_strlen.c
SOURCES += ft_strdup.c
SOURCES += ft_strsub.c
SOURCES += ft_strchr.c
SOURCES += ft_strrchr.c
SOURCES += ft_strrev.c
SOURCES += ft_strstr.c
SOURCES += ft_strtolower.c
SOURCES += ft_strtoupper.c
SOURCES += ft_strisnum.c

# Array
SRC_SUBDIR += array
SOURCES += array_create.c
SOURCES += array_init.c
SOURCES += array_clone.c
SOURCES += array_reserve.c
SOURCES += array_shrink_to_fit.c
SOURCES += array_truncate.c
SOURCES += array_clear.c
SOURCES += array_getset.c
SOURCES += array_index_of.c
SOURCES += array_insert.c
SOURCES += array_replace.c
SOURCES += array_get_available.c
SOURCES += array_remove.c
SOURCES += array_stack.c
SOURCES += array_find_from.c
SOURCES += array_swap.c

# String
SRC_SUBDIR += string
SOURCES += string_create.c
SOURCES += string_init.c
SOURCES += string_dup.c
SOURCES += string_clone.c
SOURCES += string_merge.c
SOURCES += string_cat.c
SOURCES += string_replace.c
SOURCES += string_insert.c
SOURCES += string_remove.c
SOURCES += string_reserve.c
SOURCES += string_shrink_to_fit.c
SOURCES += string_truncate.c
SOURCES += string_fmt.c

# Debug
SRC_SUBDIR += debug
SOURCES += print_memory.c

# Convert
SRC_SUBDIR += convert
SOURCES += ft_toa_base.c
SOURCES += ft_ato_base.c

# IO
SRC_SUBDIR += io
SOURCES += ft_put.c
SOURCES += ft_put_fd.c
SOURCES += ft_printf.c
SOURCES += ft_printf_core.c
SOURCES += ft_dprintf.c
SOURCES += ft_asprintf.c
SOURCES += ft_snprintf.c
SOURCES += safe_write.c
SOURCES += conv_c.c
SOURCES += conv_s.c
SOURCES += conv_wc.c
SOURCES += conv_wcs.c
SOURCES += conv_d.c
SOURCES += conv_uo.c
SOURCES += conv_x.c
SOURCES += conv_prc.c
SOURCES += utf8.c
SOURCES += str_formatting.c
SOURCES += int_formatting.c
SOURCES += parsing.c
SOURCES += utils.c

# List
SRC_SUBDIR += list
SOURCES += list_clear.c
SOURCES += list_create.c
SOURCES += list_get_set.c
SOURCES += list_init.c
SOURCES += list_insert.c
SOURCES += list_new_node.c
SOURCES += list_pop.c
SOURCES += list_push.c
SOURCES += list_remove.c
SOURCES += list_map.c
SOURCES += list_apply.c
SOURCES += list_fold.c
SOURCES += list_filter.c

# Getopt
SRC_SUBDIR += getopt
SOURCES += ft_getopt.c

# Generation
INC_PATH = inc
SRC_PATH = src
CFLAGS += $(addprefix -I,$(INC_PATH))
vpath %.c $(addprefix $(SRC_PATH)/,$(SRC_SUBDIR))

# Object files
OBJ_PATH = .obj
OBJECTS = $(SOURCES:%.c=$(OBJ_PATH)/%.o)

# Dependencies
DEP_PATH = .dep
DEPS = $(SOURCES:%.c=$(DEP_PATH)/%.d)

BUILD_DIR = $(OBJ_PATH) $(DEP_PATH)

# Rules
.PHONY: all

.SECONDARY: $(OBJECTS)

all: $(DEPS) $(NAME)

-include $(DEPS)

$(NAME): $(OBJECTS)
	ar rcs $@ $^

$(OBJECTS): $(OBJ_PATH)/%.o: %.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) -o $@ -c $<

$(DEP_PATH)/%.d: %.c | $(DEP_PATH)
	$(CC) $(CFLAGS) -MM $< -MT $(OBJ_PATH)/$*.o -MF $@

$(BUILD_DIR):
	@-mkdir -p $@

.PHONY: check clean clean-macos fclean re sanitize unsanitize

check: sanitize
	cd test && ./RunTests.sh

clean:
	$(RM) -r $(OBJ_PATH)

clean-macos:
	$(RM) -r *.dSYM/

fclean: clean
	$(RM) $(NAME)
	$(RM) $(DEPS)

re: fclean all

sanitize:
	$(MAKE) -C ./ re SAN=yes DEBUG=yes

unsanitize:
	$(MAKE) -C ./ re DEBUG=yes

# Tools
.PHONY: norme valgrind ctags

norme:
	@ ! norminette -R CheckTopCommentHeader $(SRC_PATH) | grep -v -B 1 "^Norme"
	@ ! norminette -R CheckTopCommentHeader $(INC_PATH) | grep -v -B 1 "^Norme"

valgrind:
	valgrind --leak-check=full ./$(NAME)

callgrind:
	valgrind --tool=callgrind --callgrind-out-file=$(CG_OUTPUT_FILE) ./$(NAME)
	callgrind_annotate --auto=yes $(CG_OUTPUT_FILE)

ctags:
	ctags -R --tag-relative=yes --exclude='.git*' --exclude='test' --exclude='*.o' --exclude='*dSYM' --exclude='doc' --exclude='exercices'

