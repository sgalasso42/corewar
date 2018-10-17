/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhondt <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 21:50:06 by adhondt           #+#    #+#             */
/*   Updated: 2018/07/19 12:57:24 by adhondt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	ft_putstr_fd(char const *s, int fd)
{
	char *str;

	str = (char *)s;
	while (*str)
	{
		ft_putchar_fd(*str, fd);
		str++;
	}
}
