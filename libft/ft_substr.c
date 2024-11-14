/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:48:57 by mgavorni          #+#    #+#             */
/*   Updated: 2023/11/19 16:23:56 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	unsigned int	i;
	size_t			j;
	size_t			size;
	char			*ret;

	i = 0;
	j = 0;
	while (s[i] && i < start)
		i++;
	if (ft_strlen(&s[i]) > len)
		size = len;
	else
		size = ft_strlen(&s[i]);
	ret = (char *)malloc(sizeof(char) * (size + 1));
	if (!ret)
		return (NULL);
	while (s[i + j] && j < len)
	{
		ret[j] = s[i + j];
		j++;
	}
	ret[j] = 0;
	return (ret);
}
