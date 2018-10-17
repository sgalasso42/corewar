/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puttable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 20:15:38 by akarasso          #+#    #+#             */
/*   Updated: 2018/07/31 02:51:29 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	ft_puttable(char *tab)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (i != MEM_SIZE)
	{
		ft_putchar(tab[i]);
		if (j == 2)
		{
			ft_putchar(' ');
			j = 0;
		}
		j++;
		i++;
	}
}
