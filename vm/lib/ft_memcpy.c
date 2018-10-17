/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhondt <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 21:47:14 by adhondt           #+#    #+#             */
/*   Updated: 2017/11/27 18:20:19 by adhondt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*dss;
	char	*srr;

	i = 0;
	dss = (char *)dest;
	srr = (char *)src;
	if (dss == srr || n == 0)
		return (dss);
	while (n > 0)
	{
		dss[i] = srr[i];
		n--;
		i++;
	}
	return (dss);
}
