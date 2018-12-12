#ifndef STR_42_H
# define STR_42_H

# include <stdbool.h>
# include <stddef.h>
# include <sys/types.h>

# define ASCII_TABLE_LEN (127)

char		*ft_strdup(const char *s1);
char		*ft_strndup(const char *s1, size_t n);

int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
bool		ft_streq(const char *s1, const char *s2);

size_t		ft_strlen(const char *s);
size_t		ft_strnlen(const char *s, size_t maxlen);

char		*ft_strchr(const char *s, int c);
char		*ft_strnchr(const char *s, int c, size_t n);

char		*ft_strrchr(const char *s, int c);
char		*ft_strrnchr(const char *s, int c, size_t n);

ssize_t		ft_strchrpos(const char *s, int c);
ssize_t		ft_strnchrpos(const char *s, int c, size_t n);

ssize_t		ft_strrchrpos(const char *s, int c);
ssize_t		ft_strrnchrpos(const char *s, int c, size_t n);

char		*ft_strsub(char const *s, unsigned int start, size_t len);
char		*ft_strrev(char *str);

char		*ft_strstr(const char *big, const char *little);
char		*ft_strnstr(const char *big, const char *little, size_t len);

char		*ft_strtoupper(char *str);
char		*ft_strtolower(char *str);

bool		ft_strisnum(const char *str);

#endif
