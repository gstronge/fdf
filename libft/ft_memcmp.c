/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:14:21 by gstronge          #+#    #+#             */
/*   Updated: 2024/03/11 19:30:08 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned long	i;
	unsigned char	*chars1;
	unsigned char	*chars2;

	chars1 = (unsigned char *)s1;
	chars2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (chars1[i] != chars2[i])
			return (chars1[i] - chars2[i]);
		i++;
	}
	i--;
	return (chars1[i] - chars2[i]);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	*s1 = "teste";
// 	char	*s2 = "teste";
// 	size_t	n = 0;

// 	printf("%d \n", ft_memcmp(s1, s2, n));
// 	printf("%d \n", memcmp(s1, s2, n));
// }