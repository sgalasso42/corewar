/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_champ.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 02:46:02 by akarasso          #+#    #+#             */
/*   Updated: 2018/08/01 19:43:13 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

static int	attribute_id(t_board *bd, t_champ *champ, int t[2], char **argv)
{
	if (!t[1])
		champ->player_id = get_first_number(bd, 1);
	else
	{
		if (ft_atoi(argv[t[0] + 1]) < -16 || ft_atoi(argv[t[0] + 1]) > 16)
			return (ft_error(2, 0));
		champ->player_id = get_first_number(bd, ft_atoi(argv[t[0] + 1]));
	}
	return (1);
}

int			check_size(t_champ *champ)
{
	unsigned int	size;

	if (lseek(champ->fd, PROG_NAME_LENGTH + 4 + 4, SEEK_SET) < 0)
	{
		return (ft_error(4, 1));
	}
	if (read(champ->fd, (char *)&size, 4) < 4)
		return (ft_error(3, 1));
	size = ((size >> 24) & 0xff)
		| ((size << 8) & 0xff0000)
		| ((size >> 8) & 0xff00)
		| ((size << 24) & 0xff000000);
	if (!size)
		return (ft_error(5, 0));
	if (size > CHAMP_MAX_SIZE)
		return (ft_error(4, 0));
	champ->header_champsize = size;
	return (1);
}

int			collect_comment(t_champ *champ)
{
	char	comment[COMMENT_LENGTH + 1];

	if (!(check_size((champ))))
		return (0);
	if (read(champ->fd, comment, COMMENT_LENGTH) < COMMENT_LENGTH)
		return (ft_error(3, 1));
	comment[COMMENT_LENGTH] = '\0';
	if (!(champ->comment = ft_strdup(comment)))
		return (ft_error(1, 0));
	champ->next = NULL;
	champ->process_count = 1;
	return (1);
}

int			collect_champion_data(int fd, t_champ **champ)
{
	unsigned char	magic[5];
	char			str[PROG_NAME_LENGTH + 1];

	if (!((*champ) = (t_champ *)malloc(sizeof(t_champ))))
		return (ft_error(1, 0));
	(*champ)->fd = fd;
	if (read(fd, magic, 4) < 4)
		return (ft_error(3, 1));
	if (!((int)magic[1] == 234 && (int)magic[2] == 131 && (int)magic[3] == 243))
		return (ft_error(3, 0));
	if (read(fd, str, PROG_NAME_LENGTH) < PROG_NAME_LENGTH)
		return (ft_error(3, 1));
	str[PROG_NAME_LENGTH] = '\0';
	if (!((*champ)->name = ft_strdup(str)))
	{
		free(*champ);
		return (ft_error(1, 0));
	}
	if (!(collect_comment(*champ)))
	{
		free((*champ)->name);
		free(*champ);
		return (0);
	}
	return (1);
}

int			open_champ(t_board *bd, char **argv, int i, int op)
{
	int		fd;
	t_champ	*champ;

	if (ft_strlen(argv[i + op]) <= 4 || !ft_strcmp(argv[i + op]
		+ ft_strlen(argv[i + op] - 4), ".cor"))
		return (ft_error(3, 0));
	if ((fd = open(argv[i + op], O_RDONLY)) == -1)
		return (ft_error(3, 1));
	if (!(collect_champion_data(fd, &champ)))
		return (0);
	if (!(attribute_id(bd, champ, (int[2]){i, op}, argv)))
		return (0);
	add_champ_to_lst(bd, champ);
	return (1);
}
