/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 20:15:38 by akarasso          #+#    #+#             */
/*   Updated: 2018/07/30 23:23:32 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	aff(t_board *bd, t_process *proc)
{
	char	r;

	if (bd->ram[MEM_MOD(proc->pc + 2)] > 0
		&& bd->ram[MEM_MOD(proc->pc + 2)] < 16)
	{
		r = proc->r[bd->ram[MEM_MOD(proc->pc + 2)] - 1] % 256;
		ft_putstr("Aff:");
		write(1, &r, 1);
		write(1, "\n", 1);
	}
	proc->pc += 3;
}
