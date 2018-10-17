/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   purge_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 17:22:21 by akarasso          #+#    #+#             */
/*   Updated: 2018/08/01 17:04:24 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	verbosity(t_board *bd, t_process *proc)
{
	ft_putstr("Process #");
	ft_putnbr(proc->id_process);
	ft_putstr(" die...");
	if (bd->m && proc->will_die)
		ft_putstr(" because last instruction has failed...");
	ft_putstr("\n");
}

void		free_process(t_process *proc)
{
	free(proc);
}

void		pkill(t_board *bd, t_process **last, t_process **curr)
{
	t_process *tmp;

	tmp = (*curr)->next;
	if (!(*last))
	{
		free_process(*curr);
		bd->lst_process->process = tmp;
		*curr = tmp;
	}
	else
	{
		(*last)->next = tmp;
		free_process(*curr);
		*curr = tmp;
	}
}

void		purge_process(t_board *bd)
{
	t_process *proc;
	t_process *last;

	proc = bd->lst_process->process;
	last = 0;
	while (proc)
	{
		if (proc->last_live <= bd->last_check_purge
			|| (bd->m && proc->will_die))
		{
			if (bd->verbose[1])
				verbosity(bd, proc);
			update_process_count(bd, proc->id_player, -1);
			pkill(bd, &last, &proc);
		}
		else
		{
			last = proc;
			proc = proc->next;
		}
	}
}
