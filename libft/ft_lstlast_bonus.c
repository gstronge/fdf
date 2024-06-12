/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:12:28 by gstronge          #+#    #+#             */
/*   Updated: 2024/03/14 18:43:52 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// typedef struct s_list
// {
// 	void			*content;
// 	struct s_list	*next;
// }	t_list;

// t_list	*ft_lstnew(void *content)
// {
// 	t_list	*node;

// 	node = (t_list *)malloc(1 * sizeof(t_list));
// 	if (node == NULL)
// 		return (NULL);
// 	node->content = content;
// 	node->next = NULL;
// 	return (node);
// }

// void	ft_lstadd_front(t_list **lst, t_list *new)
// {
// 	new->next = *lst;
// 	*lst = new;
// }

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

// #include <stdio.h>

// int	main(void)
// {
// 	t_list	*head;
// 	int		cont = 5;
// 	int		*content = &cont;
// 	t_list	*node2;
// 	int		cont2 = 3;
// 	int		*content2 = &cont2;
// 	t_list	*node3;
// 	int		cont3 = 1;
// 	int		*content3 = &cont3;
// 	t_list	*tail;

// 	head = ft_lstnew(content);
// 	node2 = ft_lstnew(content2);
// 	node3 = ft_lstnew(content3);

// 	ft_lstadd_front(&head, node2);
// 	ft_lstadd_front(&head, node3);

//     tail = head;
// 	tail = ft_lstlast(tail);
// }