#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include "str_42.h"
#include "io_42.h"

static int		read_line(t_gnl *gnl)
{
	char	buffer[GNL_BUFF_SIZE];
	char	*tmp;

	while (gnl->eol == NULL)
	{
		if ((gnl->reads = read(gnl->fd, buffer, GNL_BUFF_SIZE - 1)) == -1)
			return (-1);
		if (gnl->reads == 0)
			return (0);
		buffer[gnl->reads] = '\0';
		tmp = gnl->str;
		gnl->str = ft_strjoin(tmp, buffer);
		free(tmp);
		gnl->eol = ft_strchr(gnl->str, '\n');
	}
	return (gnl->reads);
}

static char		*split_line(t_gnl *gnl)
{
	size_t	len;
	char	*tmp;
	char	*line;

	len = (gnl->eol - (gnl->str + gnl->offset));
	line = ft_strsub(gnl->str, gnl->offset, len);
	gnl->offset += len + 1;
	if ((gnl->eol = ft_strchr(gnl->str + gnl->offset, '\n')) != NULL)
		return (line);
	if ((len = ft_strlen(gnl->str + gnl->offset)) > 0)
	{
		tmp = gnl->str;
		gnl->str = ft_strsub(gnl->str, gnl->offset, len);
		free(tmp);
	}
	else
	{
		free(gnl->str);
		gnl->str = NULL;
	}
	gnl->offset = 0;
	return (line);
}

static t_gnl	*get_fd(int fd, t_array *v_fd)
{
	t_gnl			*p;
	size_t			i;

	if (TARRAY_DATA(v_fd) == NULL)
		array_init(v_fd, 8);
	i = 0;
	while (i < TARRAY_COUNT(v_fd))
	{
		p = array_get(v_fd, i++);
		if (p->fd == fd)
			return (p);
	}
	p = ft_memalloc(sizeof(t_gnl));
	if (p == NULL)
		return (NULL);
	array_add(v_fd, p);
	p->fd = fd;
	return (p);
}

static void		remove_fd(int fd, t_array *v_fd)
{
	t_gnl	*p;
	size_t	i;

	i = 0;
	while (i < TARRAY_COUNT(v_fd))
	{
		p = array_get(v_fd, i);
		if (p->fd == fd)
		{
			array_remove(v_fd, i);
			free(p);
			return ;
		}
		++i;
	}
}

int				get_next_line(int const fd, char **line)
{
	static t_array	v_fd;
	t_gnl			*gnl;

	if (GNL_BUFF_SIZE <= 0 || fd < 0 || line == NULL)
		return (-1);
	if ((gnl = get_fd(fd, &v_fd)) == NULL)
		return (-1);
	if (gnl->eol == NULL)
		if (read_line(gnl) == -1)
			return (-1);
	if (gnl->reads == 0)
	{
		if ((*line = gnl->str) == NULL)
		{
			remove_fd(fd, &v_fd);
			return (0);
		}
		gnl->str = NULL;
	}
	else
		*line = split_line(gnl);
	return (1);
}
