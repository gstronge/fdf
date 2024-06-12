/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:42:16 by gstronge          #+#    #+#             */
/*   Updated: 2024/03/08 11:18:27 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (c < 48 || (c > 57 && c < 65) || (c > 90 && c < 97) || c > 122)
		return (0);
	return (1);
}

// #include <ctype.h>
// #include <stdio.h>

// int main(void)
// {
// 	int c = 128;
// 	printf("%d \n", isalnum(c));
// 	printf("%d", ft_isalnum(c));
// }