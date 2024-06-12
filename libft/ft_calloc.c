/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:53:02 by gstronge          #+#    #+#             */
/*   Updated: 2024/03/15 10:33:58 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	int	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_memset(ptr, 0, (size * count));
	return ((void *)ptr);
}

// #include <stdio.h>

// int	main(void)
// {
// 	size_t	count = 3;
// 	size_t	size = sizeof(int);
// 	int		*intptr;
// 	int		i;

// 	intptr = ft_calloc(count, size);
// 	i = 0;
// 	while (i < count)
// 	{
// 		printf("%d ", intptr[i]);
// 		i++;
// 	}
// }