/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 23:09:25 by akarasso          #+#    #+#             */
/*   Updated: 2018/08/01 14:31:17 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	verbosity(t_board *bd, t_process *proc, int data[3])
{
	ft_putstrnbrstr("Player ", proc->id_player, " // Process ");
	ft_putnbrstrnbr(proc->id_process, "\nSt r", bd->ram[MEM_MOD(proc->pc + 2)]);
	(data[2] == REG_CODE) ? ft_putstrnbrstr(" to r", data[0], "") :
	ft_putstrnbrstr(" to ", data[1], "");
	ft_putstr("\n\n");
}

static int	valid_args(t_board *bd, t_process *proc, int ocp, int value)
{
	if (ocp == REG_CODE && (value < 1 || value > 16))
		return (0);
	if (bd->ram[MEM_MOD(proc->pc + 2)] < 1
		|| bd->ram[MEM_MOD(proc->pc + 2)] > 16)
		return (0);
	return (1);
}

void		st(t_board *bd, t_process *proc)
{
	int		ocp;
	int		value_reg;
	int		value;

	ocp = ocp_scd(bd->ram[MEM_MOD(proc->pc + 1)]);
	value = (ocp == REG_CODE) ?
		bd->ram[MEM_MOD(proc->pc + 3)] : get_indir(bd, proc->pc + 3);
	if (valid_args(bd, proc, ocp, value))
	{
		value_reg = proc->r[bd->ram[MEM_MOD(proc->pc + 2)] - 1];
		if (ocp == REG_CODE)
			proc->r[value - 1] = value_reg;
		else
			set_ramvalue(bd, proc->pc + (value % IDX_MOD), value_reg);
		proc->carry = (!(value_reg)) ? 1 : 0;
		if (bd->verbose[1])
			verbosity(bd, proc, (int[3]){value, value_reg, ocp});
	}
	else if (bd->m)
		proc->will_die = 1;
	proc->pc += (ocp == IND_CODE) ? 5 : 4;
}
