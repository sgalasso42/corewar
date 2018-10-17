/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 23:25:08 by akarasso          #+#    #+#             */
/*   Updated: 2018/07/31 01:19:28 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	verbosity(t_process *proc, t_process *new)
{
	ft_putstrnbrstr("Player ", new->id_player, " // Process ");
	ft_putnbrstrnbr(proc->id_process, "\nFork, new PC on ", MEM_MOD(new->pc));
	ft_putstrnbrstr(". Carry : ", new->carry, "\n\n");
}

void		frk(t_board *bd, t_process *proc)
{
	t_process		*new;
	int				newpc;
	int				i;

	i = 0;
	newpc = get_dir2(bd, proc->pc + 1);
	if ((new = add_process(bd, proc->id_player, proc->pc)))
	{
		while (i < 16)
		{
			new->r[i] = proc->r[i];
			i++;
		}
		new->last_live = proc->last_live;
		new->carry = proc->carry;
		new->pc = proc->pc + (newpc % IDX_MOD);
		update_process_count(bd, proc->id_player, 1);
		if (bd->verbose[1])
			verbosity(proc, new);
	}
	proc->pc += 3;
}
