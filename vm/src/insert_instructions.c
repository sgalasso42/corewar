/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_instructions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 20:15:38 by akarasso          #+#    #+#             */
/*   Updated: 2018/08/01 00:14:44 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

static int		insert_code(t_board *bd, int pos)
{
	t_champ			*tmp;
	unsigned char	str;
	int				size;

	size = 0;
	tmp = bd->first_champ;
	while (tmp->next && tmp->next->fd != 0)
		tmp = tmp->next;
	if (lseek(tmp->fd, 2192, SEEK_SET) < 0)
		return (ft_error(4, 1));
	while (read(tmp->fd, &str, 1) > 0)
	{
		bd->ram[pos] = (unsigned char)str;
		pos++;
		size++;
	}
	if (tmp->header_champsize != size)
		return (ft_error(4, 0));
	bd->last_live = tmp->player_id;
	close(tmp->fd);
	tmp->fd = 0;
	return (1);
}

int				insert_instructions(t_board *bd)
{
	unsigned int	i;
	int				j;

	i = 0;
	j = 0;
	while (i < bd->champions_count)
	{
		if (!insert_code(bd, (j * i++)))
			return (0);
		j = MEM_SIZE / bd->champions_count;
	}
	return (1);
}
