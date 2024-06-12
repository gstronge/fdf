/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:05:30 by gstronge          #+#    #+#             */
/*   Updated: 2024/03/15 10:20:44 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

// #include <stdio.h>
// #include <string.h>

// int main(void)
// {
// 	char *s = "123";
// 	printf("%lu \n", strlen(s));
// 	printf("%lu", ft_strlen(s));
// }