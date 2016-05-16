#ifndef GNL_H
# define GNL_H
# define BUFF_SIZE 8

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "libft/libft.h"

int		get_next_line(const int fd, char **line);

#endif
