/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:32:15 by gstronge          #+#    #+#             */
/*   Updated: 2024/03/15 10:03:24 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if (c > 122 || c < 65 || (c > 90 && c < 97))
	{
		return (0);
	}
	return (1);
}

// #include <ctype.h>
// #include <stdio.h>

// int main(void)
// {
// 	int c = 98;
// 	printf("%d \n", isalpha(c));
// 	printf("%d", ft_isalpha(c));
// }