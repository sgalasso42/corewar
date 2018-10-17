/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_inputs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 01:11:55 by akarasso          #+#    #+#             */
/*   Updated: 2018/08/01 14:22:31 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

static int		dump(t_board *bd, char **argv, int i)
{
	int	dump;

	dump = ft_atoi(argv[i + 1]);
	if (dump < 0)
		return (0);
	bd->dump = dump;
	return (1);
}

static int		get_verbose(t_board *bd, char *arg)
{
	int	level;

	level = ft_atoi(arg);
	if (level < 0 || level > 4)
		return (0);
	bd->verbose[level] = 1;
	return (1);
}

static int		check_arg_ii(t_board *bd, char **argv, int *i, int n)
{
	if (n == 1)
	{
		if (!argv[*i + 1] || !ft_isnumber(argv[*i + 1]) || !dump(bd, argv, *i))
			return (ft_error(2, 0));
		*i += 1;
	}
	else if (n == 2)
		if (!argv[(*i) + 1] || !ft_isnumber(argv[(*i) + 1]) ||
				!get_verbose(bd, argv[(*i) + 1]))
			return (ft_error(2, 0));
		else
			*i += 1;
	else if (n == 3)
		bd->p = MAX_PROC;
	else if (n == 4)
		bd->s = 1;
	else if (n == 5)
		bd->m = 1;
	else if (!open_champ(bd, argv, *i, 0))
		return (0);
	return (1);
}

static int		check_arg(t_board *bd, char **argv, int *i)
{
	static char	*opt_list[7] = {"-n", "-d", "-v", "-p", "-s", "-m", NULL};
	int			n;

	n = 6;
	if (argv[*i][0] == '-' && (n = pos_str_tab(argv[*i], opt_list)) == -1)
		return (ft_error(2, 0));
	else if (n == 0)
	{
		if (!argv[*i + 1] || !argv[*i + 2] || !ft_isnumber(argv[*i + 1]))
			return (ft_error(2, 0));
		if (!open_champ(bd, argv, *i, 2))
			return (0);
		*i += 2;
	}
	else
		return (check_arg_ii(bd, argv, i, n));
	return (1);
}

t_board			*collect_inputs(char **argv, int argc, t_board *bd)
{
	int	i;

	i = 1;
	while (argv[i] && i < argc)
	{
		if (!(check_arg(bd, argv, &i)))
			return (NULL);
		i++;
	}
	return (bd);
}
