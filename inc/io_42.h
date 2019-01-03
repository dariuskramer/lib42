#ifndef IO_42_H
# define IO_42_H

# include <stddef.h>
# include <sys/types.h>
# include <stdarg.h>
# include <wchar.h>
# include <stdlib.h>
# include <unistd.h>
# include "memory_42.h"
# include "str_42.h"
# include "string_42.h"
# include "convert_42.h"
# include "ctype_42.h"
# include "macros_42.h"

# define SPECIFIERS "csCSdouxXp%"

# ifndef MB_LEN_MAX
#  define MB_LEN_MAX 4
# endif

typedef struct	s_gnl
{
	char		*str;
	char		*eol;
	int			fd;
	int			offset;
	int			reads;
}				t_gnl;

typedef struct	s_format
{
	unsigned	f_sharp;
	unsigned	f_zero;
	unsigned	f_minus;
	unsigned	f_space;
	unsigned	f_plus;
	unsigned	min_width;
	int			prec;
	char		len_mod;
	char		conv;
	char		no_conv;
	char		pad[1];
}				t_format;

typedef	int		(*t_fc)(t_string*, t_format*, va_list);

ssize_t			io_safe_write(const t_string *buf, int fd);
void			ft_putchar(char c);
void			ft_putstr(char const *c);
void			ft_putendl(char const *c);
void			ft_putnbr(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *c, int fd);
void			ft_putendl_fd(char const *c, int fd);
void			ft_putnbr_fd(int n, int fd);

/*
** standard printf flavors
*/
ssize_t			ft_printf(const char *format, ...);
ssize_t			ft_dprintf(int fd, const char *format, ...);
ssize_t			ft_vprintf(const char *format, va_list ap);
ssize_t			ft_vdprintf(int fd, const char *format, va_list ap);

/*
** internals
*/
t_string		*io_fmt(t_string *buf, const char *format, va_list ap);
int				parse_conv(char c, t_format *fmt);
char			*parse_flags(char *format, t_format *fmt);
char			*parse_min_width(char *format, t_format *fmt);
char			*parse_precision(char *format, t_format *fmt);
char			*parse_len_mod(char *format, t_format *fmt);
int				conv_c(t_string *b, t_format *fmt, va_list ap);
int				conv_s(t_string *b, t_format *fmt, va_list ap);
int				conv_wc(t_string *b, t_format *fmt, va_list ap);
int				conv_wcs(t_string *b, t_format *fmt, va_list ap);
int				conv_d(t_string *b, t_format *fmt, va_list ap);
int				conv_o(t_string *b, t_format *fmt, va_list ap);
int				conv_u(t_string *b, t_format *fmt, va_list ap);
int				conv_x(t_string *b, t_format *fmt, va_list ap);
int				conv_p(t_string *b, t_format *fmt, va_list ap);
int				conv_prc(t_string *b, t_format *fmt, va_list ap);
int				str_formatting(t_string *pb, t_format *fmt, size_t arglen);
int				int_format_intro(t_format *fmt, char *arg, size_t *arglen);
int				int_sign(t_string *pb, t_format *fmt, char *arg);
int				int_padding(t_string *pb, t_format *fmt, size_t arglen,
		int fchar);
int				int_precision(t_string *pb, t_format *fmt, size_t arglen);
int				ft_wctomb(char *s, wchar_t wchar);
size_t			ft_wcstombs(char *s, wchar_t *pwcs, size_t n);
size_t			ft_wcslen(const wchar_t *s);
int				conv_to_utf8(int wbytes, wchar_t wchar, char *s);

#endif
