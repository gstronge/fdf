/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:46:17 by gstronge          #+#    #+#             */
/*   Updated: 2024/03/14 11:31:55 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_check_needle(const char *haystack, const char *needle, int i)
{
	int		j;

	j = 0;
	while (needle[j] != '\0')
	{
		if (needle[j] != haystack[i])
			return (0);
		j++;
		i++;
	}
	return (1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned long	i;
	unsigned long	j;
	char			*ptr;
	unsigned long	nlen;

	i = 0;
	j = 0;
	nlen = 0;
	while (needle[nlen] != '\0')
		nlen++;
	if (needle[i] == '\0')
		return (ptr = (char *)&haystack[i]);
	while (i < len && haystack[i] != '\0')
	{
		if (haystack[i] == needle[0] && (nlen + i) <= len)
		{
			if (ft_check_needle(haystack, needle, i))
			{
				return (ptr = (char *)&haystack[i]);
			}
		}
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	*haystack = "asfbgfdabgasdfasgshtdrardrsdf";
// 	char	*needle = "";
// 	size_t	len = 5;

// 	printf("%s\n", ft_strnstr(haystack, needle, len));
// 	printf("%s\n", strnstr(haystack, needle, len));
// }