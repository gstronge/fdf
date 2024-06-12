/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:43:54 by gstronge          #+#    #+#             */
/*   Updated: 2024/03/11 17:19:14 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned long	i;
	unsigned long	dstlen;
	unsigned long	srclen;
	unsigned long	result;

	i = 0;
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (dstlen >= dstsize)
		return (dstsize + srclen);
	if (dstlen + srclen >= dstsize)
	{
		result = srclen + dstlen;
		srclen = dstsize - dstlen - 1;
	}
	else
		result = dstlen + srclen;
	while (i < srclen)
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	return (result);
}

// #include <string.h>
// #include <stdio.h>

// int main(void)
// {
// 	char dst[13] = "pqrs";
// 	const char *src = "abcdefghi";
// 	size_t dstsize = 13;

// 	// dst[0] = '0';
// 	// dst[1] = '1';
// 	// dst[2] = '2';
// 	// dst[3] = '3';
// 	// dst[4] = '4';
// 	// dst[5] = '5';

// 	printf("%s \n", dst);
// 	printf("%zu \n", ft_strlcat(dst, src, dstsize));
// 	// printf("%zu \n", strlcat(dst, src, dstsize));
// 	printf("%s \n", dst);
// }