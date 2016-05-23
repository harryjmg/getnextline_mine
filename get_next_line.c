/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgueguen <hgueguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 20:21:48 by hgueguen          #+#    #+#             */
/*   Updated: 2014/04/20 21:42:48 by hgueguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static int			verif_nl(char *stock)
{
	int				i;
	int				d;

	i = 0;
	d = 0;
	while (stock[i])
	{
		if (stock[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char			*add_to_stock(char *stock, char *buf, int ret)
{
	int				len;
	char			*new_stock;

	len = ft_strlen(stock);
	new_stock = (char *)malloc(sizeof(char) * (len + ret + 1));
	new_stock[0] = 0;
	ft_strcat(new_stock, stock);
	ft_strcat(new_stock, buf);
	return (new_stock);
}

static char			*get_line(char **stock)
{
	int				i;
	char			*s;
	char			*line;

	s = *stock;
	i = 0;
	while (s[i] != '\n' && s[i] != 0)
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (s[i] != '\n' && s[i] != 0)
	{
		line[i] = s[i];
		i++;
	}
	*stock = *stock + i + 1;
	line[i] = '\0';
	return (line);
}

int					get_next_line(int const fd, char **line)
{
	int				ret;
	char			buf[BUFF_SIZE + 1];
	static char		*stock = "";

	if (fd < 0 || !line)
		return (-1);
	ret = read(fd, buf, BUFF_SIZE);
	if (ret == -1)
		return (-1);
	buf[ret] = '\0';
	stock = add_to_stock(stock, buf, ret);
	while (verif_nl(stock) == 0 && ret != 0)
	{
		ft_bzero(buf, BUFF_SIZE);
		ret = read(fd, buf, BUFF_SIZE);
		buf[ret] = '\0';
		stock = add_to_stock(stock, buf, ret);
	}
	if (ft_strlen(stock) == 0 && ret <= BUFF_SIZE)
		return (0);
	*line = get_line(&stock);
	return (1);
}
