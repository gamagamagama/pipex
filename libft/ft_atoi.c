/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:48:55 by matus             #+#    #+#             */
/*   Updated: 2023/11/19 16:19:49 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	z;
	int	nmbr;

	i = 0;
	z = 1;
	nmbr = 0;
	while (nptr[i] == ' ' || nptr[i] == '\n' || nptr[i] == '\t'
		|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
		{
			z *= -1;
		}
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		nmbr = nmbr * 10 + (nptr[i] - '0');
		i++;
	}
	return (nmbr * z);
}
