/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:16:52 by gstronge          #+#    #+#             */
/*   Updated: 2024/03/15 10:44:03 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c > 64 && c < 91)
		c += 32;
	return (c);
}

// #include <stdio.h>
// #include <ctype.h>

// int main(void)
// {
// 	int	c = 'A';
// 	printf("%d \n", tolower(c));
// 	printf("%d", ft_tolower(c));
// }