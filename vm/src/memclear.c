/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memclear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 20:15:38 by akarasso          #+#    #+#             */
/*   Updated: 2018/07/30 23:14:20 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	clear_champ(t_champ *champ)
{
	t_champ *next;

	while (champ)
	{
		next = champ->next;
		free(champ->name);
		free(champ->comment);
		free(champ);
		champ = next;
	}
}

void	clear_process(t_process *proc)
{
	t_process *next;

	while (proc)
	{
		next = proc->next;
		free(proc);
		proc = next;
	}
}

void	memclear(t_board *bd)
{
	if (bd)
	{
		if (bd->lst_process)
		{
			clear_process(bd->lst_process->process);
			free(bd->lst_process);
		}
		if (bd->first_champ)
			clear_champ(bd->first_champ);
		if (bd->ram)
			free(bd->ram);
		if (bd->ram)
			free(bd->verbose);
		free(bd);
	}
}
