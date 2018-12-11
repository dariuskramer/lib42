#ifndef MACROS_42_H
# define MACROS_42_H

# define FT_ABS(x)        (((x) < 0) ? -(x) : (x))
# define FT_MAX(a, b)     ((a) < (b) ? (b) : (a))
# define FT_MIN(a, b)     ((a) > (b) ? (b) : (a))
# define ARR_SIZ_MAX(a)   (sizeof(a) / sizeof((a)[0]))
# define IS_POWER_OF_2(n) ((((n) - 1) & (n)) == 0)
# define ROUND_UP_16(n)   (!(n) || (n) % 16U ? ((n) + 16U) & (~0U - 15U) : (n))
# define ROUND_UP_8(n)    (!(n) || (n) % 8U ? ((n) + 8U) & (~0U - 7U) : (n))

#endif
