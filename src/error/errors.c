#if defined(__linux__)
# define _GNU_SOURCE
#endif

#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "str_42.h"
#include "io_42.h"
#include "error_42.h"

static char 		*g_context;
static const char	*g_project_name;

void	die(const char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

void	error_register_project_name(const char *project_name)
{
	g_project_name = project_name;
}

void	error_set_context(const char *format, ...)
{
	t_string	buf;
	va_list		args;

	assert(format != NULL);
	va_start(args, format);
	if (string_init(&buf) == NULL || ft_printf_fmt(&buf, format, args) == NULL)
		die(FATAL_MALLOC);
	g_context = buf.str;
	va_end(args);
}

void	error_print(const char *msg)
{
	assert(g_project_name != NULL);
	if (g_context == NULL)
	{
		ft_dprintf(2, "%s: %s\n", g_project_name, msg);
	}
	else
	{
		ft_dprintf(2, "%s: %s: %s\n", g_project_name, msg, g_context);
		free(g_context);
		g_context = NULL;
	}
}
