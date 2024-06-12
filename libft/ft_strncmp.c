/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:22:24 by gstronge          #+#    #+#             */
/*   Updated: 2024/03/11 19:14:50 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned long	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] != '\0' && s2[i] != '\0' && i < n)
	{
		if (s1[i] != s2[i])
		{
			break ;
		}
		if (i == n - 1)
			return (s1[i] - s2[i]);
		i++;
	}
	return ((const unsigned char)s1[i] - (const unsigned char)s2[i]);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	*s1 = "abcdefgh";
// 	char	*s2 = "abcdwxyz";
// 	size_t	n = 4;

// 	printf("%d \n", strncmp(s1, s2, n));
// 	printf("%d \n", ft_strncmp(s1, s2, n));
// }