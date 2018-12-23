#ifndef GETOPT_42_H
# define GETOPT_42_H

# include <stddef.h>
# include <stdbool.h>

# define GETOPT_INVALID_ERR_FORMAT "%s: invalid option -- '%c'\n"
# define GETOPT_MULT_ERR_FORMAT "%s: option '%c' requires an argument\n"
# define OPT_INIT(o) ((o) = (t_opt){NULL, 1, 1, 1, -1, false})

typedef struct	s_opt
{
	const char	*arg;
	size_t		end;
	unsigned	current_arg;
	unsigned	current_opt;
	int			unknown_opt;
	bool		print_errmsg;
}				t_opt;

int				ft_getopt(const char *const *av, const char *optstr,
		t_opt *opt);

#endif
