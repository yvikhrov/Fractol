/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 20:57:37 by yvikhrov          #+#    #+#             */
/*   Updated: 2018/02/04 13:01:36 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd(t_list **alst, t_list *new)
{
	t_list	*head;

	if (!new || !alst)
		return ;
	if (!(head = *alst))
		*alst = new;
	else
	{
		*alst = new;
		new->next = head;
	}
}
