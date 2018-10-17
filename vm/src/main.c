/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 20:15:38 by akarasso          #+#    #+#             */
/*   Updated: 2018/08/01 14:38:12 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	init_struct(t_board *bd)
{
	bd->lst_process = NULL;
	bd->first_champ = NULL;
	bd->champions_count = 0;
	bd->cycle = 0;
	bd->id_process = 0;
	bd->last_live = 0;
	bd->last_check_purge = 0;
	bd->check_nbr = 0;
	bd->total_cycle_live = 0;
	bd->ram = NULL;
	bd->dump = -1;
	bd->cycle_to_die = 0;
	bd->opt_list = NULL;
	bd->verbose = NULL;
	bd->p = 0;
	bd->m = 0;
	bd->s = 0;
}

int		init_board_data(t_board **bd, char **argv)
{
	int i;

	i = 0;
	if (!bd || !(*bd = (t_board *)malloc(sizeof(t_board))))
		return (ft_error(1, 0));
	init_struct(*bd);
	while (argv[++i])
		if (ft_strlen(argv[i]) >= 5
			&& !ft_strcmp(argv[i] + ft_strlen(argv[i]) - 4, ".cor"))
			(*bd)->champions_count++;
	if ((*bd)->champions_count > 4 || (*bd)->champions_count < 1)
		return (ft_error(6, 0));
	if (!((*bd)->ram = ft_memalloc_c(MEM_SIZE, 0)))
		return (ft_error(1, 0));
	if (!((*bd)->verbose = ft_memalloc(5)))
		return (ft_error(1, 0));
	return (1);
}

int		error_management(t_board *fucked_board)
{
	memclear(fucked_board);
	ft_putstr("ERROR MANAGEMENT MESSAGE LEAKS TO ERASE ERROR\n");
	return (-1);
}

void	show_winner(t_board *bd)
{
	t_champ	*champ;
	char	*tmp;

	champ = bd->first_champ;
	while (champ)
	{
		if (champ->player_id == bd->last_live)
		{
			if (bd->s)
			{
				tmp = ft_strjoin(ft_strdup("say 'And the winner is "),
					escape_champ(champ->name));
				tmp = ft_strjoin(tmp, ft_strdup("'"));
				system(tmp);
				free(tmp);
			}
			ft_putstr("Winner: Player#");
			ft_putnbr(champ->player_id);
			ft_putstr(" connu sour le nom de ");
			ft_putstr(champ->name);
			ft_putstr("\n");
			return ;
		}
		champ = champ->next;
	}
}

int		main(int argc, char **argv)
{
	t_board	*board;

	board = NULL;
	if (argc < 2)
		return (ft_usage());
	if (!init_board_data(&board, argv)
		|| !collect_inputs(argv, argc, board)
			|| !insert_instructions(board))
		return (error_management(board));
	if (board->verbose[0])
		print_champ_lst(board);
	if (board->s)
		sount_start_game();
	play(board);
	show_winner(board);
	if (board->verbose[4])
		print_memory(board, 0);
	memclear(board);
	return (0);
}
