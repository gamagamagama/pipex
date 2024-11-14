/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:26:25 by mgavorni          #+#    #+#             */
/*   Updated: 2023/11/19 16:20:45 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!ft_lstsize(lst))
	{
		return (NULL);
	}
	while ((*lst).next)
	{
		lst = (*lst).next;
	}
	return (lst);
}
