/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:00:37 by mgavorni          #+#    #+#             */
/*   Updated: 2023/11/19 16:23:53 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_verify(char c, const char *set)
{
	while (*set)
	{
		if (c == *set++)
		{
			return (1);
		}
	}
	return (0);
}

static int	ft_start_index(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (ft_verify(s1[i], set) && s1[i])
	{
		i++;
	}
	return (i);
}

static int	ft_end_index(char const *s1, char const *set)
{
	int	len;

	len = ft_strlen(s1) - 1;
	while (ft_verify(s1[len], set) && s1[len])
	{
		len--;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		i;
	char	*n_str;

	start = ft_start_index(s1, set);
	end = ft_end_index(s1, set);
	if (start > end)
	{
		n_str = malloc(1);
		n_str[0] = 0;
		return (n_str);
	}
	n_str = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!n_str)
		return (NULL);
	i = 0;
	while (start <= end)
	{
		n_str[i] = s1[start];
		i++;
		start++;
	}
	n_str[i] = '\0';
	return (n_str);
}
