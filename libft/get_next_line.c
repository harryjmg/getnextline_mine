/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorimba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/14 15:38:41 by rkorimba          #+#    #+#             */
/*   Updated: 2014/05/01 16:24:39 by hgueguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

static void			add_str(char **line, char *str)
{
	size_t			i;
	char			*tmp;
	size_t			len;

	i = 0;
	if (*line)
	{
		tmp = ft_strdup(*line);
		free(*line);
		len = ft_strlen(tmp) + ft_strlen(str);
		*line = (char *)malloc(sizeof(char) * (len + 1));
		ft_strcpy(*line, tmp);
		free(tmp);
		while ((*line)[i])
			i++;
	}
	else
	{
		len = ft_strlen(str);
		*line = (char *)malloc(sizeof(char) * (len + 1));
	}
	while (*str != '\0' && *str != '\n')
		(*line)[i++] = *str++;
	(*line)[i] = '\0';
}

static char			*set_rest(char *str)
{
	while (*str != '\n' && *str != '\0')
		str++;
	if (*str == '\n')
		return (ft_strdup(++str));
	else
		return (NULL);
}

static int			init_with_rest(char **line, char **rest)
{
	char			*del;

	if (*rest && ft_strchr(*rest, '\n'))
	{
		add_str(line, *rest);
		del = *rest;
		*rest = set_rest(del);
		free(del);
		return (1);
	}
	else if (*rest && !ft_strchr(*rest, '\n'))
	{
		*line = ft_strdup(*rest);
		free(*rest);
		*rest = NULL;
	}
	return (0);
}

static int			start(char **line, char **rest, int const fd)
{
	if (!line)
		line = (char **)malloc(sizeof(char *));
	if (*line)
		free(*line);
	*line = NULL;
	if (BUFF_SIZE <= 0 || fd < 0)
		return (-1);
	if (init_with_rest(line, rest))
		return (1);
	return (0);
}

int					get_next_line(int const fd, char **line)
{
	char			*str;
	static char		*rest = NULL;
	size_t			ret;
	int				check;

	check = start(line, &rest, fd);
	if (check != 0)
		return (check);
	str = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	while ((ret = read(fd, str, BUFF_SIZE)) > 0 && !ft_strchr(str, '\n'))
	{
		str[ret] = '\0';
		add_str(line, str);
	}
	if (ret > 0)
	{
		str[ret] = '\0';
		add_str(line, str);
		rest = set_rest(str);
	}
	free(str);
	if (ret > 1)
		ret = 1;
	return (ret);
}
