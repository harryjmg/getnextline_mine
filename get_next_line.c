#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFF_SIZE 1

static int			search_line(char *str)
{
	int				i;

	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}

static char			*extract_line(char *stock, int nl_pos, char **line)
{
	char			*new_stock;
	int				i;
	int				j;

	j = nl_pos;
	if (j == 0)
		j = strlen(stock);
	*line = (char *)malloc(sizeof(char) * (j + 1));
	i = 0;
	while (i < j)
	{
		(*line)[i] = stock[i];
		i++;
	}
	(*line)[i] = 0;
	if (nl_pos == 0)
		new_stock = strdup(stock + j);
	else
		new_stock = strdup(stock + j + 1);
	return (new_stock);
}

static char			*push_to_stock(char *stock, char *buf)
{
	char			*new_stock;

	new_stock = (char *)malloc(sizeof(strlen(stock) + strlen(buf) + 2));
	new_stock[0] = 0;
	new_stock = strcat(new_stock, stock);
	new_stock = strcat(new_stock, buf);
	return (new_stock);
}

int					get_next_line(int const fd, char **line)
{
	static char		*stock = "";
	int				ret;
	char			buf[BUFF_SIZE + 1];

	if (fd < 0 || !line)
		return (-1);
	if (search_line(stock))
	{
		stock = extract_line(stock, search_line(stock), line);
		return (1);
	}
	printf("1\n");
	while (search_line(stock) == 0 && (ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		printf("o");
		buf[ret] = 0;
		stock = push_to_stock(stock, buf);
	}
	printf("2\n");
	if (ret == 0 && search_line(stock) == 0)
	{
		printf("ret 0\n");
		return (0);
	}
	printf("3\n");
	stock = extract_line(stock, search_line(stock), line);
	printf("4 [%s]\n", stock);
	return (1);
}

int					main()
{
	char			*line;
	int				ret;
	int				fd;

	// line = 0;
	// av[1] = extract_line(av[1], 0, &line);
	// printf("[%s]\n", line);
	// printf("[%s]\n", av[1]);
	// line = 0;
	// get_next_line(0, &line);
	// printf("[%s]\n", line);
	// line = 0;
	// get_next_line(0, &line);
	// printf("[%s]\n", line);
	// line = 0;
	// get_next_line(0, &line);
	// printf("[%s]\n", line);
	fd = open("test", O_RDONLY);
	line = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		printf("-> [%s] [%d]\n", line, ret);\
		line = 0;
	}
	return (0);
}