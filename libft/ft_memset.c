/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:42:28 by gstronge          #+#    #+#             */
/*   Updated: 2024/03/15 10:21:20 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned long	i;
	char			*ptr;

	i = 0;
	ptr = (char *)b;
	while (i < len)
	{
		ptr[i] = (char)c;
		i++;
	}
	return (b);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	b[11] = "0123456789";
// 	int		c = 67;
// 	size_t	len = 15;

// 	memset(b, c, len);
// 	printf("%s \n", b);
// 	// ft_memset(b, c, len);
// 	// printf("%s \n", b);
// }