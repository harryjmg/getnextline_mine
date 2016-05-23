/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgueguen <hgueguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 18:46:40 by hgueguen          #+#    #+#             */
/*   Updated: 2013/11/29 21:13:28 by hgueguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s1[j] != 0)
		j++;
	while (s2[i] != 0)
	{
		s1[i + j] = s2[i];
		i++;
	}
	s1[i + j] = 0;
	return (s1);
}
