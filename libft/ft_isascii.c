/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:42:16 by gstronge          #+#    #+#             */
/*   Updated: 2024/03/08 11:30:40 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c < 0 || c > 127)
		return (0);
	return (1);
}

// #include <ctype.h>
// #include <stdio.h>

// int main(void)
// {
// 	int c = 128;
// 	printf("%d \n", isascii(c));
// 	printf("%d", ft_isascii(c));
// }