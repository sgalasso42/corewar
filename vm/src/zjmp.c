/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 23:06:25 by akarasso          #+#    #+#             */
/*   Updated: 2018/07/30 23:08:28 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	verbosity(t_process *proc, int val)
{
	ft_putstrnbrstr("Player ", proc->id_player, " // Process ");
	ft_putnbrstrnbr(proc->id_process, "\nZjmp to ", (val));
	proc->carry ? ft_putstr("Success\n\n") : ft_putstr("Failed\n\n");
}

void		zjmp(t_board *bd, t_process *proc)
{
	int	val;

	val = get_dir2(bd, proc->pc + 1);
	if (proc->carry)
		proc->pc += (val % IDX_MOD);
	else
		proc->pc += 3;
	if (bd->verbose[1])
		verbosity(proc, val);
}
