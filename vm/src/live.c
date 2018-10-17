/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 21:01:46 by akarasso          #+#    #+#             */
/*   Updated: 2018/08/01 14:39:21 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	verbosity(t_process *proc, int val)
{
	ft_putstr("Player #");
	ft_putnbr(proc->id_player);
	ft_putstr(" // Process ");
	ft_putnbr(proc->id_process);
	ft_putstr("\nLive ");
	ft_putnbr(val);
	ft_putstr("\n\n");
}

static int	is_true_player(t_board *bd, int val)
{
	t_champ *champ;

	champ = bd->first_champ;
	while (champ)
	{
		if (champ->player_id == val)
			return (1);
		champ = champ->next;
	}
	return (0);
}

void		live(t_board *bd, t_process *proc)
{
	int				val;

	val = get_dir4(bd, proc->pc + 1);
	proc->last_live = bd->cycle;
	bd->total_cycle_live++;
	if (is_true_player(bd, val))
		bd->last_live = val;
	proc->pc += 5;
	if (bd->verbose[1])
		verbosity(proc, val);
}
