/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 23:01:41 by akarasso          #+#    #+#             */
/*   Updated: 2018/08/01 14:33:51 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		verbosity(t_board *bd, t_process *proc, int *val)
{
	ft_putstrnbrstr("Player ", proc->id_player, " // Process ");
	ft_putnbrstrnbr(proc->id_process,
			"\nSti r", bd->ram[MEM_MOD(proc->pc + 2)]);
	ft_putstrnbrstr(" to ", val[1], " + ");
	ft_putnbrstrnbr(val[2], " = ", val[1] + val[2]);
	ft_putstrnbrstr(" (with PC and mod at : ",
			(proc->pc + ((val[1] + val[2]) % IDX_MOD)), "). Carry :");
	ft_putnbr(proc->carry);
	ft_putstr(".\n\n");
}

static	int		get_value(t_board *bd, int *pc, int ocp, int flag)
{
	int res;

	res = 0;
	if (ocp == REG_CODE)
	{
		res = bd->ram[MEM_MOD(*pc)];
		(*pc) += 1;
	}
	else if (ocp == DIR_CODE)
	{
		res = (flag) ? get_dir4(bd, *pc) : get_dir2(bd, *pc);
		(*pc) += (flag) ? 4 : 2;
	}
	else if (ocp == IND_CODE)
	{
		res = (flag) ? get_indir(bd, *pc) : get_indir(bd, *pc);
		(*pc) += 2;
	}
	return (res);
}

static int		valid_args(t_board *bd, t_process *proc, int *ocp, int *val)
{
	if (val[0] < 1 || val[0] > 16)
		return (0);
	if (ocp[1] == REG_CODE && (val[1] < 1 || val[1] > 16))
		return (0);
	val[0] = proc->r[val[0] - 1];
	if (ocp[1] == REG_CODE)
		val[1] = proc->r[val[1] - 1];
	else if (ocp[1] == IND_CODE)
		val[1] = get_dir2(bd, proc->pc + val[1]);
	if (ocp[2] == REG_CODE)
		val[2] = proc->r[val[2] - 1];
	return (1);
}

static void		get_values(t_board *bd, int *offset, int *ocp, int *val)
{
	int i;

	i = 0;
	while (i < 3)
	{
		val[i] = get_value(bd, offset, ocp[i], 0);
		i++;
	}
}

void			sti(t_board *bd, t_process *proc)
{
	int	ocp[3];
	int	val[3];
	int	offset;

	offset = proc->pc + 2;
	ocp[0] = REG_CODE;
	ocp[1] = ocp_scd(bd->ram[MEM_MOD(proc->pc + 1)]);
	ocp[2] = ocp_third(bd->ram[MEM_MOD(proc->pc + 1)]);
	get_values(bd, &offset, ocp, val);
	if (valid_args(bd, proc, ocp, val))
	{
		set_ramvalue(bd, (proc->pc + ((val[1] + val[2]) % IDX_MOD)), val[0]);
		proc->carry = (!val[0]) ? 1 : 0;
		if (bd->verbose[1])
			verbosity(bd, proc, val);
	}
	else if (bd->m)
		proc->will_die = 1;
	proc->pc = offset;
}
