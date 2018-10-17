/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 23:05:59 by akarasso          #+#    #+#             */
/*   Updated: 2018/08/01 19:42:57 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

int		ft_usage(void)
{
	ft_putstr("./corewar [-d, -n, -v] <champion1.cor> <..> [1 - 4 .cor]\n");
	ft_putstr("-d N : Dump Memory at N cycles [0 - ...]\n");
	ft_putstr("-n N <champ.cor> : Attribute N [-16 - 16]");
	ft_putstr(" as player number to champ.cor\n");
	ft_putstr("-v N : Display level [1 - 4] :\n");
	ft_putstr("\t0: Display Champions data\n");
	ft_putstr("\t1: Display all Operations\n");
	ft_putstr("\t2: Display informations before each CYCLE_TO_DEATH\n");
	ft_putstr("\t3: Display information and RAM after each CYCLE_TO_DEATH\n");
	ft_putstr("\t4: Display the final RAM status\n");
	return (1);
}

int		ft_error(int id, int errn)
{
	if (id == 1)
		ft_putstr_fd("ERROR: Memory Allocation failed.\n\n", 2);
	else if (id == 2)
		ft_putstr_fd("ERROR: Wrong flag usage.\n\n", 2);
	else if (id == 3)
	{
		ft_putstr_fd("ERROR : Wrong [champion].cor file", 2);
		if (errn == 1)
			ft_put3str(" -> ", strerror(errno), ".\n\n");
		else
			ft_putstr(".\n\n");
	}
	else if (id == 4)
		ft_putstr_fd("ERROR: Invalid [champion].cor header\n\n", 2);
	else if (id == 5)
		ft_putstr_fd("ERROR: Invalid size\n\n", 2);
	else if (id == 6)
	{
		ft_putstr_fd("ERROR: Wrong [champion].cor count [1 - 4]\n\n", 2);
	}
	ft_usage();
	return (0);
}

void	print_verbose_data(t_board *bd)
{
	t_champ *tmp;

	tmp = bd->first_champ;
	ft_putstr("Cycle number: ");
	ft_putnbr(bd->cycle);
	ft_putstr(" // Cycle to die: ");
	ft_putnbr(bd->cycle_to_die);
	ft_putstr("\nTotal live instruction during cycle: ");
	ft_putnbr(bd->total_cycle_live);
	ft_putstr("\n--- --- ---\n");
	while (tmp)
	{
		ft_putstr("Champion name: ");
		ft_putstr(tmp->name);
		ft_putstr("\nTotal living processus: ");
		ft_putnbr(tmp->process_count);
		ft_putstr("\n--- --- ---\n");
		tmp = tmp->next;
	}
}

void	print_memory(t_board *bd, int id)
{
	unsigned char	j;
	int				i;

	i = 0;
	while (i != MEM_SIZE)
	{
		j = (bd->ram[i] / 16) + 48;
		j > '0' ? ft_putstr("\033[0;31m") : 0;
		j > '9' ? ft_putchar(j + 39) : ft_putchar(j);
		j = (bd->ram[i] % 16) + 48;
		j > '0' ? ft_putstr("\033[0;31m") : 0;
		j > '9' ? ft_putchar(j + 39) : ft_putchar(j);
		ft_putchar(' ');
		i++;
		ft_putstr("\033[0m");
	}
	ft_putchar('\n');
	if (id == 1)
		print_verbose_data(bd);
}

void	print_champ_lst(t_board *bd)
{
	t_champ	*tmp;
	int		i;

	i = 0;
	tmp = bd->first_champ;
	while (tmp)
	{
		if (i++ == 0)
			ft_putstr("--- --- ---\n");
		ft_putstr("Champion name: [");
		ft_putstr(tmp->name);
		ft_putstr("] Player id: [");
		ft_putnbr(tmp->player_id);
		ft_putstr("]\nChampion comment : ");
		ft_putstr(tmp->comment);
		ft_putstr("\n");
		tmp = tmp->next;
		ft_putstr("--- --- ---\n");
	}
}
