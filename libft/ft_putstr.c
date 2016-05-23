/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgueguen <hgueguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/25 11:06:11 by hgueguen          #+#    #+#             */
/*   Updated: 2013/11/25 11:07:34 by hgueguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putstr(char const *s)
{
	int i;

	i = 0;
	while (s[i] != 0)
	{
		ft_putchar(s[i]);
		i++;
	}
}
