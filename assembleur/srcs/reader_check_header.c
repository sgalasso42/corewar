/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_check_header.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 21:53:25 by sgalasso          #+#    #+#             */
/*   Updated: 2018/08/01 19:16:46 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		ft_handle_name(char *line, t_data *data)
{
	int		i;
	int		start;
	char	*tmp;

	i = 6;
	while (line[i] && line[i] != '"')
		i++;
	if (line[i] != '"')
		return (0);
	start = i++;
	while (line[i] && line[i] != '"')
		i++;
	if (!line[i] || (line[i] != '"' && line[i + 1] != 0))
		return (0);
	if (ft_strlen(line) - (start + 2) > PROG_NAME_LENGTH)
		return (0);
	tmp = data->name;
	if (!(data->name =
	ft_strsub(line, start + 1, ft_strlen(line) - (start + 2))))
	{
		ft_strdel(&tmp);
		return (0);
	}
	ft_strdel(&tmp);
	return (1);
}

int		ft_handle_comment(char *line, t_data *data, int fd)
{
	int	start;
	int ret;
	int i;

	ret = 0;
	i = 9;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] != '"')
		return (0);
	start = ++i;
	while (line[i] && line[i] != '"')
		i++;
	if ((ret = reader_first(line, data, start, i)) == 0)
		return (0);
	else if (ret == 1)
		return (1);
	if (line[i] != '"' && reader_multiple(line, fd, data))
		return (1);
	return (0);
}

int		reader_check_header(t_data *data, char *line, int fd)
{
	if (reader_is_empty(line))
		return (1);
	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_is_name(line) && ft_handle_name(line, data))
		return (1);
	if (ft_is_comment(line) && ft_handle_comment(line, data, fd))
		return (1);
	return (0);
}
