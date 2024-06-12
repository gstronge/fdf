/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:30:47 by gstronge          #+#    #+#             */
/*   Updated: 2024/03/15 11:45:37 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_zero(char *ptr)
{
	ptr = (char *)malloc(2 * sizeof(char));
	if (ptr == NULL)
		return (ptr = NULL);
	ptr[0] = '0';
	ptr[1] = '\0';
	return (ptr);
}

static	char	*ft_write_num(char *ptr, int len, long i, int minus)
{
	ptr[len] = '\0';
	while (len > 0)
	{
		len--;
		ptr[len] = (i % 10) + '0';
		i = i / 10;
	}
	if (minus == -1)
		ptr[0] = '-';
	return (ptr);
}

static	int	ft_lencalc(int len, long i)
{
	if (i < 0)
	{
		i = -i;
		len++;
	}
	while (i > 0)
	{
		len++;
		i = i / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		len;
	long	i;
	int		minus;

	len = 0;
	minus = 1;
	i = n;
	ptr = NULL;
	if (n == 0)
		return (ft_zero(ptr));
	if (i < 0)
	{
		minus = -1;
	}
	len = ft_lencalc(len, i);
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (ptr = NULL);
	i = n;
	i = minus * i;
	ptr = ft_write_num(ptr, len, i, minus);
	return (ptr);
}

// #include <stdio.h>

// int	main(void)
// {
// 	int	n = 2147483647;
// 	// int	n = -2147483648;

// 	printf("%s", ft_itoa(n));
// }