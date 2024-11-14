/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:03:37 by mgavorni          #+#    #+#             */
/*   Updated: 2023/11/19 16:22:22 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*new_s;

	i = 0;
	j = 0;
	if (!(s1) || !(s2))
		return (NULL);
	new_s = (char *)malloc(((ft_strlen(s1)) + (ft_strlen(s2)) + 1)
			* (sizeof(char)));
	if (!new_s)
		return (NULL);
	while (s1[i])
	{
		new_s[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		new_s[i + j] = s2[j];
		j++;
	}
	new_s[i + j] = '\0';
	return (new_s);
}
