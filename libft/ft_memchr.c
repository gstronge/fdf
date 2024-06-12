/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:51:23 by gstronge          #+#    #+#             */
/*   Updated: 2024/03/11 19:12:05 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned long	i;
	char			*ptr;

	i = 0;
	c = (char)c;
	ptr = (char *)s;
	while (i < n)
	{
		if (ptr[i] == c)
		{
			return ((void *)&ptr[i]);
		}
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	const char	*s = "asdfZskljgdafghfjkhdfZz";
// 	int			c = 90;
// 	size_t		n = 10;

// 	printf("%s \n", ft_memchr(s, c, n));
// 	printf("%s \n", memchr(s, c, n));
// }