/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:24:32 by mgavorni          #+#    #+#             */
/*   Updated: 2023/11/19 16:22:26 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	leftlen;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	leftlen = size - dstlen - 1;
	if (size <= dstlen)
	{
		return (srclen + size);
	}
	if (srclen < leftlen)
	{
		ft_memcpy(dst + dstlen, src, srclen);
		dst[dstlen + srclen] = '\0';
	}
	else
	{
		ft_memcpy(dst + dstlen, src, leftlen);
		dst[dstlen + leftlen] = '\0';
	}
	return (dstlen + srclen);
}
