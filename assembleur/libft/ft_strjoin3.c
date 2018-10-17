/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 16:43:22 by akarasso          #+#    #+#             */
/*   Updated: 2018/08/01 16:45:38 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	int		len_1;
	int		len_2;
	int		len_3;
	char	*ptr;

	if (!s1 || !s2 || !s3)
		return (0);
	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	len_3 = ft_strlen(s3);
	if (!(ptr = malloc(sizeof(char) * (len_1 + len_2 + len_3) + 1)))
		return (0);
	ft_strcpy(ptr, s1);
	ft_strcpy(ptr + len_1, s2);
	ft_strcpy(ptr + len_1 + len_2, s3);
	return (ptr);
}
