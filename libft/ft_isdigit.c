/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:30:14 by gstronge          #+#    #+#             */
/*   Updated: 2024/03/08 11:30:25 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c > 57 || c < 48)
		return (0);
	return (1);
}

// #include <ctype.h>
// #include <stdio.h>

// int main(void)
// {
// 	int c = 47;
// 	printf("%d \n", isdigit(c));
// 	printf("%d", ft_isdigit(c));
// }