#ifndef CONVERT_42_H
# define CONVERT_42_H

# include <stddef.h>
# include <sys/types.h>

char	*ft_utoa_base_r(char *buf, unsigned long long n, unsigned base);
char	*ft_utoa_base(unsigned long long n, unsigned base);
char	*ft_stoa_base_r(char *buf, long long n, unsigned base);
char	*ft_stoa_base(long long n, unsigned base);
size_t	ft_atou_base(const char *str, unsigned base);
ssize_t	ft_atoi_base(const char *str, unsigned base);
size_t	ft_atou(const char *str);

#endif
