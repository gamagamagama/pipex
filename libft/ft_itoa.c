/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:23:28 by matus             #+#    #+#             */
/*   Updated: 2023/11/19 16:20:17 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	numlen(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		i++;
	if (n == 0)
		i++;
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*num_str;
	int		len;
	int		sign;

	len = numlen(n);
	sign = 1;
	num_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!num_str)
		return (0);
	num_str[len] = 0;
	len--;
	if (n < 0)
	{
		num_str[0] = '-';
		sign = -1;
	}
	if (n == 0)
		num_str[len] = '0';
	while (n != 0)
	{
		num_str[len] = (n % 10 * sign) + '0';
		n /= 10;
		len--;
	}
	return (num_str);
}
