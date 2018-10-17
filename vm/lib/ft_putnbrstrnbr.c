/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrstrnbr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 20:10:54 by adhondt           #+#    #+#             */
/*   Updated: 2018/07/31 02:52:13 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	ft_putnbrstrnbr(int nb, char *str, int n)
{
	ft_putnbr(nb);
	ft_putstr(str);
	ft_putnbr(n);
	return ;
}
