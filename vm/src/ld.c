/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 21:01:53 by akarasso          #+#    #+#             */
/*   Updated: 2018/08/01 19:30:31 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	verbosity(t_process *proc, int value, int reg)
{
	ft_putstrnbrstr("Player ", proc->id_player, " // Process ");
	ft_putnbrstrnbr(proc->id_process, "\nLd ", value);
	ft_putstrnbrstr(" in r", reg, ". Carry : ");
	ft_putnbr(proc->carry);
	ft_putstr("\n\n");
}

void		ld(t_board *bd, t_process *proc)
{
	int	ocp;
	int	reg;
	int	value;

	ocp = ocp_first(bd->ram[MEM_MOD(proc->pc + 1)]);
	value = (ocp == IND_CODE)
		? get_dir4(bd, proc->pc + (get_indir(bd, proc->pc + 2) % IDX_MOD))
		: get_dir4(bd, proc->pc + 2);
	proc->carry = (!value) ? 1 : 0;
	reg = (ocp == IND_CODE) ? bd->ram[MEM_MOD(proc->pc + 4)]
		: bd->ram[MEM_MOD(proc->pc + 6)];
	if ((ocp == REG_CODE && reg > 0 && reg < 17) || ocp != REG_CODE)
	{
		if (reg > 0 && reg < 17)
		{
			proc->r[reg - 1] = value;
			proc->carry = (!value) ? 1 : 0;
			if (bd->verbose[1])
				verbosity(proc, value, reg);
		}
	}
	else if (bd->m)
		proc->will_die = 1;
	proc->pc += (ocp == IND_CODE) ? 5 : 7;
}
