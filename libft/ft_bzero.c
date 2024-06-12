/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:42:28 by gstronge          #+#    #+#             */
/*   Updated: 2024/03/15 10:22:05 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned long	i;
	char			*ptr;

	i = 0;
	ptr = (char *)s;
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	s[11] = "0123456789";
// 	size_t	n = 5;

// 	printf("%s \n", s);
// 	ft_bzero(s, n);

// 	// printf("%s \n", s);
// 	// bzero(s, n);

// 	int i = 0;

// 	while(i < 11)
// 	{
// 		printf("%c \n", s[i]);
// 		i++;
// 	}

// }