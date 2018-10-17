/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 20:55:01 by akarasso          #+#    #+#             */
/*   Updated: 2018/07/31 00:05:28 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		check_process_status(t_board *bd)
{
	if (bd->verbose[2])
		print_verbose_data(bd);
	purge_process(bd);
	bd->last_check_purge = bd->cycle;
	if (bd->total_cycle_live >= NBR_LIVE || bd->check_nbr == MAX_CHECKS)
	{
		bd->cycle_to_die -= CYCLE_DELTA;
		bd->check_nbr = 0;
	}
	bd->check_nbr++;
	bd->total_cycle_live = 0;
	if (bd->verbose[3])
		print_memory(bd, 1);
	return ((bd->lst_process->process) != NULL && bd->cycle_to_die > 0);
}

void	run(t_board *bd)
{
	t_process		*proc;

	bd->last_check_purge = 0;
	proc = bd->lst_process->process;
	while (bd->lst_process && bd->cycle < bd->dump)
	{
		while (proc)
		{
			check_instruction(bd, proc);
			proc = proc->next;
		}
		if ((bd->last_check_purge == bd->cycle - bd->cycle_to_die
			&& !check_process_status(bd)) || (bd->cycle_to_die <= 0))
			break ;
		bd->cycle++;
		proc = bd->lst_process->process;
	}
}

void	play(t_board *board)
{
	if (board->champions_count < 1)
		return ;
	if (!init_process(board))
		return ;
	board->cycle_to_die = CYCLE_TO_DIE;
	run(board);
}
