/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 20:15:38 by akarasso          #+#    #+#             */
/*   Updated: 2018/08/01 14:28:27 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	verbosity(t_board *bd, t_process *proc, int ocp, int val)
{
	ft_putstrnbrstr("Player ", proc->id_player, " // Process ");
	if (ocp == DIR_CODE)
	{
		ft_putnbrstrnbr(proc->id_process, "\nLld ", val);
		ft_putstrnbrstr(" in r", bd->ram[MEM_MOD(proc->pc + 6)], ". Carry : ");
	}
	else
	{
		ft_putnbrstrnbr(proc->id_process, "\nLld ",
			get_dir2(bd, proc->pc + val));
		ft_putstrnbrstr(" in r", bd->ram[MEM_MOD(proc->pc + 4)], ". Carry : ");
	}
	ft_putnbr(proc->carry);
	ft_putstr("\n");
}

static int	valid_args(t_board *bd, t_process *proc, int ocp)
{
	if (ocp == DIR_CODE
		&& (bd->ram[MEM_MOD(proc->pc + 6)] < 1
			|| bd->ram[MEM_MOD(proc->pc + 6)] > 16))
		return (0);
	else if (ocp != DIR_CODE
		&& (bd->ram[MEM_MOD(proc->pc + 4)] < 1
			|| bd->ram[MEM_MOD(proc->pc + 4)] > 16))
		return (0);
	return (1);
}

void		lld(t_board *bd, t_process *proc)
{
	int	ocp;
	int	value;

	ocp = ocp_first(bd->ram[MEM_MOD(proc->pc + 1)]);
	value = (ocp == DIR_CODE) ? get_dir4(bd, proc->pc + 2) :
		get_dir2(bd, proc->pc + get_long_indir(bd, proc->pc + 2));
	if (valid_args(bd, proc, ocp))
	{
		if (ocp == DIR_CODE)
			proc->r[bd->ram[MEM_MOD(proc->pc + 6)] - 1] = value;
		else
			proc->r[bd->ram[MEM_MOD(proc->pc + 4)] - 1] = value;
		proc->carry = (!value) ? 1 : 0;
		if (bd->verbose[1])
			verbosity(bd, proc, ocp, value);
	}
	else if (bd->m)
		proc->will_die = 1;
	proc->pc += (ocp == DIR_CODE) ? 7 : 5;
}
