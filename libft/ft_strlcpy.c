/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:22:34 by gstronge          #+#    #+#             */
/*   Updated: 2024/03/08 14:23:25 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned long	i;
	int				len;

	i = 0;
	len = 0;
	while (src[len] != '\0')
		len++;
	if (dstsize <= 0)
		return (len);
	while (src[i] != '\0' && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}

// #include <string.h>
// #include <stdio.h>

// int main(void)
// {
// 	char dst[10];
// 	const char *src = "asd";
// 	size_t dstsize = 0;

// 	dst[0] = '0';
// 	dst[1] = '1';
// 	dst[2] = '2';
// 	dst[3] = '3';
// 	dst[4] = '4';
// 	dst[5] = '5';

// 	printf("%s \n", dst);
// 	// printf("%zu \n", ft_strlcpy(dst, src, dstsize));
// 	printf("%zu \n", strlcpy(dst, src, dstsize));
// 	printf("%s \n", dst);
// }