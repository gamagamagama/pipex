/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:54:10 by matus             #+#    #+#             */
/*   Updated: 2023/11/19 16:21:03 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ps;
	unsigned char	pc;

	ps = (unsigned char *)s;
	pc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (*ps == pc)
		{
			return (ps);
		}
		i++;
		ps++;
	}
	return (NULL);
}
