/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:17:20 by gstronge          #+#    #+#             */
/*   Updated: 2024/03/11 11:25:08 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	num;
	int		minus;

	i = 0;
	num = 0;
	minus = 1;
	while (str[i] != '\0' && (str[i] == ' ' || str[i] == '\t' || \
	str[i] == '\v' || str[i] == '\n' || str[i] == '\r' || str[i] == '\f'))
		i++;
	if (str[i] == '-')
	{
		minus = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i] - 48);
		i++;
	}
	return (num * minus);
}

// #include <stdio.h>
// #include <stdlib.h>

// int main(void)
// {
// 	const char *str = "  \n  -+231sd2540";

// 	printf("%d \n", ft_atoi(str));
// 	printf("%d \n", atoi(str));
// }