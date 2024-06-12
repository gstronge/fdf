/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:42:02 by gstronge          #+#    #+#             */
/*   Updated: 2024/03/15 11:46:18 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_empty_str(char *ptr)
{
	ptr = (char *)malloc((1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ptr[0] = '\0';
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned long	i;
	char			*ptr;

	i = 0;
	ptr = (char *)s;
	while (ptr[i] != '\0')
		i++;
	if (start >= i)
		return (ft_empty_str(ptr));
	if ((i - start) < len)
		len = i - start;
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = s[i + start];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

// #include <stdio.h>
// #include <stddef.h>

// int	main(void)
// {
// 	char			*s = "";
// 	unsigned int	start = 0;
// 	size_t			len = 0;

// 	printf("%s \n", ft_substr(s, start, len));
// 	// printf("%s \n", substr(s, start, len));
// }