#ifndef ERROR_42_H
# define ERROR_42_H

# include <errno.h>
# include <sys/errno.h>

# define FATAL_MALLOC	"fatal: malloc failed !"

typedef enum e_return_code
{
	OK_,
	ERROR_,
} t_ret;

void	error_register_project_name(const char *project_name);
void	error_set_context(const char *format, ...);
void	error_print(const char *module_name);
void	die(const char *msg);

#endif
