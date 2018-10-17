/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 00:01:59 by akarasso          #+#    #+#             */
/*   Updated: 2018/08/01 00:14:34 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		len;
	char	*new;

	len = 0;
	len += (s1) ? ft_strlen(s1) : 0;
	len += (s2) ? ft_strlen(s1) : 0;
	if (!(new = (char*)malloc(len)))
		return (0);
	if (s1)
	{
		new = ft_strcat(new, s1);
		free(s1);
	}
	if (s2)
	{
		new = ft_strcat(new, s2);
		free(s2);
	}
	return (new);
}
