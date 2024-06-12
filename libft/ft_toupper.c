/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:16:52 by gstronge          #+#    #+#             */
/*   Updated: 2024/03/08 11:29:08 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c > 96 && c < 123)
		c -= 32;
	return (c);
}

// #include <stdio.h>
// #include <ctype.h>

// int main(void)
// {
// 	int	c = 97;
// 	printf("%d \n", toupper(c));
// 	printf("%d", ft_toupper(c));
// }