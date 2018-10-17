/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 20:15:38 by akarasso          #+#    #+#             */
/*   Updated: 2018/07/30 23:17:26 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned int	ocp_first(unsigned char c)
{
	return (c >> 6);
}

unsigned int	ocp_scd(unsigned char c)
{
	return ((c >> 4) & 3);
}

unsigned int	ocp_third(unsigned char c)
{
	return ((c >> 2) & 3);
}
