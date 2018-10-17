/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 20:38:28 by meyami            #+#    #+#             */
/*   Updated: 2018/08/01 20:14:55 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	lines_free(t_line *lines)
{
	if (!lines)
		return ;
	lines_free(lines->next);
	while (lines->nb_params)
	{
		free(lines->params[lines->nb_params - 1]);
		lines->nb_params--;
	}
	free(lines->params);
	free(lines);
}

int		lines_evaluate_size(t_line *line, t_op op)
{
	int		size;
	int		direct_size;
	int		i;

	direct_size = 4 - 2 * op.direct_size;
	size = 1 + (line->params_code_byte != 0);
	i = -1;
	while (++i < line->nb_params)
	{
		size += (line->params_type[i] == T_REG)
				+ ((line->params_type[i] == T_DIR) * direct_size)
				+ ((line->params_type[i] == T_IND) * IND_SIZE);
	}
	return (size);
}

int		lines_review(t_data *data)
{
	t_line	*line;
	t_op	op;

	if (!(line = data->lines))
	{
		ft_printf("Error: no instruction.\n");
		return (0);
	}
	while (line)
	{
		line->index = data->prog_size;
		op = data->op_tab[line->command - 1];
		if (!parameters_check_legal(line, op))
			return (0);
		parameters__set_code_byte(line);
		data->prog_size += lines_evaluate_size(line, op);
		line = line->next;
	}
	return (1);
}
