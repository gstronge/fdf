/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:18:23 by gstronge          #+#    #+#             */
/*   Updated: 2024/03/15 10:35:08 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned long		i;
	unsigned char		*pdst;
	unsigned const char	*psrc;

	i = 0;
	pdst = (unsigned char *)dst;
	psrc = (unsigned const char *)src;
	if (pdst == NULL && psrc == NULL)
		return (NULL);
	while (i < n)
	{
		pdst[i] = psrc[i];
		i++;
	}
	return (dst);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	dst[] = "Learningisfun";
// 	char	src[100] = "Learningisfun";
// 	size_t	n = 10;

// 	printf("%s \n", src);
// 	ft_memcpy(src +8, src, n);
// 	// memcpy(src +8, src, n);
// 	printf("%s \n", src);
// }

// // Driver program  
// int main()  
// {  
// char csrc[100] = "Geeksfor";  
// ft_memcpy(csrc+5, csrc, strlen(csrc)+1);  
// printf("%s", csrc);  
// return 0;  
// } 

// // Driver program  
// int main()  
// {  
// char csrc[] = "GeeksforGeeks";  
// char cdest[100];  
// ft_memcpy(cdest, csrc, strlen(csrc)+1);  
// printf("Copied string is %s", cdest);

// int isrc[] = {10, 20, 30, 40, 50};  
// int n = sizeof(isrc)/sizeof(isrc[0]);  
// int idest[n], i;  
// ft_memcpy(idest, isrc, sizeof(isrc));  
// printf("\nCopied array is ");  
// for (i=0; i<n; i++)  
//     printf("%d ", idest[i]);  
// return 0;  
// } 
