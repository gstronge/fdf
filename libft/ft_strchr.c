/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:59:47 by gstronge          #+#    #+#             */
/*   Updated: 2024/03/11 18:32:36 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = NULL;
	c = (char)c;
	while (s[i] != c && s[i] != '\0')
		i++;
	if (s[i] == c)
	{
		ptr = (char *)&s[i];
		return (ptr);
	}
	return (NULL);
}

// #include <string.h>
// #include <stdio.h>

// int main(void)
// {
// 	int 	c = 'e';
// 	char	*s = "teste";

// 	printf("%p \n", s);
// 	printf("%p \n", s);

// 	printf("%s \n", strchr(s, c));
// 	printf("%s \n", ft_strchr(s, c));

// 	printf("%p \n", strchr(s, c));
// 	printf("%p \n", ft_strchr(s, c));
// }