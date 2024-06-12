/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:42:16 by gstronge          #+#    #+#             */
/*   Updated: 2024/03/08 11:30:10 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c < 32 || c > 126)
		return (0);
	return (1);
}

// #include <ctype.h>
// #include <stdio.h>

// int main(void)
// {
// 	int c = 32;
// 	printf("%d \n", isprint(c));
// 	printf("%d", ft_isprint(c));
// }