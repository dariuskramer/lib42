#include "io_42.h"

static int	tables_dispatch(t_string *b, t_format *fmt, va_list ap)
{
	static char	*spec = "csCSdouxXp%";
	static t_fc	fp[11];
	size_t		i;

	fp[0] = &conv_c;
	fp[1] = &conv_s;
	fp[2] = &conv_wc;
	fp[3] = &conv_wcs;
	fp[4] = &conv_d;
	fp[5] = &conv_o;
	fp[6] = &conv_u;
	fp[7] = &conv_x;
	fp[8] = &conv_x;
	fp[9] = &conv_p;
	fp[10] = &conv_prc;
	i = 0;
	while (spec[i] != fmt->conv)
		++i;
	return (fp[i](b, fmt, ap));
}

static char	*parse_fmt(char *format, t_format *fmt)
{
	if (*format == '\0')
		return (format);
	format = parse_flags(format, fmt);
	format = parse_min_width(format, fmt);
	format = parse_precision(format, fmt);
	format = parse_len_mod(format, fmt);
	if (parse_conv(*format, fmt) == 0)
		return (format);
	return (format + 1);
}

t_string	*io_fmt(t_string *buf, const char *format, va_list ap)
{
	t_format	fmt;
	char		*pconv;

	while ((pconv = ft_strchr(format, '%')) != NULL)
	{
		ft_memset(&fmt, 0, sizeof(fmt));
		if (string_ncat(buf, format, (size_t)(pconv - format)) == NULL)
			return (NULL);
		format = parse_fmt(pconv + 1, &fmt);
		if (fmt.conv != '\0')
			if (tables_dispatch(buf, &fmt, ap) == -1)
				return (NULL);
	}
	if (*format != '\0')
		if (string_ncat(buf, format, ft_strlen(format)) == NULL)
			return (NULL);
	return (buf);
}
