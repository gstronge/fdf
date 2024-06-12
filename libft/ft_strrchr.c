/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:22:06 by gstronge          #+#    #+#             */
/*   Updated: 2024/03/11 18:37:38 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = NULL;
	c = (char)c;
	while (s[i] != '\0')
		i++;
	while (i != 0)
	{
		if (s[i] == c)
			break ;
		i--;
	}
	if (s[i] == c)
	{
		ptr = (char *)&s[i];
		return (ptr);
	}
	return (NULL);
}

// #include <string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int	c = 'e';
// 	const char	*s = "teste";

// 	printf("%p \n", s);
// 	printf("%p \n", s);

// 	printf("%s \n", strrchr(s, c));
// 	printf("%s \n", ft_strrchr(s, c));

// 	printf("%p \n", strrchr(s, c));
// 	printf("%p \n", ft_strrchr(s, c));
// }