/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:06:55 by gstronge          #+#    #+#             */
/*   Updated: 2024/03/14 11:21:15 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_memmove_write(char *ptrdst, const char *ptrsrc, size_t len)
{
	unsigned long	i;

	i = 0;
	if (ptrdst > ptrsrc)
	{
		while (0 < len)
		{
			ptrdst[len - 1] = ptrsrc[len - 1];
			len--;
		}
	}
	if (ptrdst < ptrsrc)
	{
		while (i < len)
		{
			ptrdst[i] = ptrsrc[i];
			i++;
		}
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char			*ptrdst;
	const char		*ptrsrc;

	ptrdst = (char *)dst;
	ptrsrc = (const char *)src;
	if (ptrdst == NULL && ptrsrc == NULL)
		return (NULL);
	ft_memmove_write(ptrdst, ptrsrc, len);
	return ((void *)dst);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	dst[] = "";
// 	char	src[100] = "  123456";
// 	size_t	n = 4;

// 	printf("%s \n", src);
//  	ft_memmove(src, src +2, n);
// 	// memmove(src, src +2, n);
// 	printf("%s \n", src);
// }

// GS MAIN

// #include <stdio.h>  
// #include <string.h> 
// int	main(void)
// {
// 	char	dst[] = "Learningisfun";
// 	char	src[] = "qwertyu";
// 	size_t	len = 5;

// 	printf("%s \n", dst);
// 	ft_memmove(dst, src, len);
// 	printf("%s \n", dst);
// }