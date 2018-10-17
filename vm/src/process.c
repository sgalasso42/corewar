/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 20:15:38 by akarasso          #+#    #+#             */
/*   Updated: 2018/08/01 14:30:57 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			update_process_count(t_board *bd, int id, int op)
{
	t_champ *tmp;

	tmp = bd->first_champ;
	while (tmp)
	{
		if (id == tmp->player_id)
		{
			tmp->process_count += op;
			break ;
		}
		else
			tmp = tmp->next;
	}
}

t_lst_process	*init_list_process(void)
{
	t_lst_process *lst;

	if (!(lst = (t_lst_process*)malloc(sizeof(t_lst_process))))
		return (0);
	lst->process = 0;
	lst->len = 0;
	return (lst);
}

t_process		*new_process(unsigned int id_process,
	unsigned int r1, unsigned int pc)
{
	int			i;
	t_process	*new;

	if (!(new = (t_process*)malloc(sizeof(t_process))))
		return (0);
	i = 0;
	while (i < REG_NUMBER)
		new->r[i++] = 0;
	new->pc = pc;
	new->r[0] = r1;
	new->id_player = r1;
	new->op_code = 0;
	new->last_live = 0;
	new->will_die = 0;
	new->id_process = id_process;
	new->carry = 0;
	new->next = 0;
	return (new);
}

int				could_already_create(t_board *bd, int r1)
{
	t_champ *champ;

	if (!bd->p)
		return (1);
	champ = bd->first_champ;
	while (champ)
	{
		if (champ->player_id == r1
			&& champ->process_count < (int)(bd->p / bd->champions_count))
			return (1);
		champ = champ->next;
	}
	return (0);
}

t_process		*add_process(t_board *bd, int r1, unsigned int pc)
{
	t_process	*process;
	t_process	*new;

	process = bd->lst_process->process;
	if (!could_already_create(bd, r1)
		|| !(new = new_process(bd->id_process, r1, MEM_MOD(pc))))
		return (0);
	bd->id_process++;
	if (process)
	{
		new->next = process;
		bd->lst_process->process = new;
		bd->lst_process->len++;
		return (new);
	}
	else
	{
		bd->lst_process->process = new;
		bd->lst_process->len++;
		return (new);
	}
}
