/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:03:44 by matus             #+#    #+#             */
/*   Updated: 2023/11/19 16:25:33 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t slen)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!haystack && !slen && !needle)
		return (NULL);
	if (*needle == '\0' )
	{
		return (((char *)haystack));
	}
	while (haystack[i] && i < slen)
	{
		j = 0;
		while (needle[j] == haystack[i + j] && i + j < slen)
		{
			if (needle[j + 1] == '\0')
			{
				return ((char *)haystack + i);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}
