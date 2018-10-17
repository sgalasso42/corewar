/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ramvalue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 20:15:38 by akarasso          #+#    #+#             */
/*   Updated: 2018/07/30 23:11:03 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	set_ramvalue(t_board *bd, unsigned int pc, unsigned int value)
{
	bd->ram[MEM_MOD(pc)] = value >> 24;
	bd->ram[MEM_MOD(pc + 1)] = value >> 16;
	bd->ram[MEM_MOD(pc + 2)] = value >> 8;
	bd->ram[MEM_MOD(pc + 3)] = value;
}
