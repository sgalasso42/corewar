/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_check_comment.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 16:52:32 by akarasso          #+#    #+#             */
/*   Updated: 2018/08/01 19:09:37 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		reader_first(char *line, t_data *data, int start, int i)
{
	char *tmp;

	if (line[i] == 0)
	{
		if (!(data->comment))
		{
			data->comment = ft_strdup(line + start);
			tmp = data->comment;
			data->comment = ft_strjoin(data->comment, "\n");
			ft_strdel(&tmp);
		}
	}
	else
	{
		tmp = data->comment;
		if (!(data->comment =
		ft_strsub(line, start, ft_strlen(line) - (start + 1))))
		{
			ft_strdel(&tmp);
			return (0);
		}
		ft_strdel(&tmp);
		return ((ft_strlen(data->comment) > COMMENT_LENGTH) ? 0 : 1);
	}
	return (2);
}

int		reader_end(char *pos, t_data *data, char *line)
{
	char *tmp;

	*pos = 0;
	tmp = data->comment;
	if (!(data->comment = ft_strjoin(data->comment, line)))
	{
		ft_strdel(&line);
		return (0);
	}
	ft_strdel(&tmp);
	ft_strdel(&line);
	return ((ft_strlen(data->comment) > COMMENT_LENGTH) ? 0 : 1);
}

int		reader_multiple(char *line, int fd, t_data *data)
{
	char *tmp;
	char *pos;

	while (get_next_line(fd, &line) > 0)
	{
		if ((pos = ft_strchr(line, '"')))
			return (reader_end(pos, data, line));
		tmp = data->comment;
		if (!(data->comment = ft_strjoin3(data->comment, line, "\n")))
		{
			ft_strdel(&line);
			return (0);
		}
		ft_strdel(&tmp);
		ft_strdel(&line);
		data->line_nb++;
	}
	ft_strdel(&line);
	return (1);
}
