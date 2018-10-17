/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc_c.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 18:11:02 by adhondt           #+#    #+#             */
/*   Updated: 2018/07/31 02:53:25 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

unsigned char	*ft_memalloc_c(size_t size, char c)
{
	unsigned char	*str;
	size_t			i;

	i = 0;
	if (!(str = (unsigned char *)malloc(sizeof(unsigned char) * (size + 1))))
		return (NULL);
	while (i != size)
		str[i++] = c;
	str[size] = '\0';
	return (str);
}
