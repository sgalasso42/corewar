/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 00:15:01 by akarasso          #+#    #+#             */
/*   Updated: 2018/08/01 00:42:22 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	sount_start_game(void)
{
	system("say '3'");
	sleep(1);
	system("say '2'");
	sleep(1);
	system("say '1'");
	system("say 'Happy bloodbath'");
	sleep(1);
}

char	*escape_champ(char *s)
{
	char	*new;
	int		i1;
	int		i2;

	i1 = 0;
	i2 = 0;
	if (!(new = (char *)malloc(ft_strlen(s))))
		return (0);
	while (s[i2])
	{
		if ((s[i2] >= 'A' && s[i2] <= 'Z')
			|| (s[i2] >= 'a' && s[i2] <= 'z')
			|| (s[i2] == ' '))
		{
			new[i1] = s[i2];
			i1++;
		}
		i2++;
	}
	new[i1] = 0;
	return (new);
}
