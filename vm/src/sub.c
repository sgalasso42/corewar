/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 20:15:38 by akarasso          #+#    #+#             */
/*   Updated: 2018/08/01 14:32:46 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		verbosity(t_process *proc, int val[3])
{
	ft_putstrnbrstr("\n\nPlayer ", proc->id_player, " // Process ");
	ft_putnbrstrnbr(proc->id_process, "\nSub (r", val[0]);
	ft_putstrnbrstr(" - r", val[1], ") to r");
	ft_putnbrstrnbr(val[2], " = ", val[0] - val[1]);
	ft_putstrnbrstr(". Carry : ", proc->carry, "\n\n");
}

static int		valid_args(int val[3])
{
	int i;

	i = 0;
	while (i < 3)
	{
		if (val[i] < 1 || val[i] > 16)
			return (0);
		i++;
	}
	return (1);
}

void			sub(t_board *bd, t_process *proc)
{
	int	val[3];

	val[0] = bd->ram[MEM_MOD(proc->pc + 2)];
	val[1] = bd->ram[MEM_MOD(proc->pc + 3)];
	val[2] = bd->ram[MEM_MOD(proc->pc + 4)];
	if (valid_args(val))
	{
		val[0] = proc->r[val[0] - 1];
		val[1] = proc->r[val[1] - 1];
		proc->carry = (!(val[0] - val[1])) ? 1 : 0;
		proc->r[val[2] - 1] = (val[0] - val[1]);
		if (bd->verbose[1])
			verbosity(proc, val);
	}
	else if (bd->m)
		proc->will_die = 1;
	proc->pc += 5;
}
