/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:04:06 by gstronge          #+#    #+#             */
/*   Updated: 2024/03/14 11:41:25 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_joincpy(char const *s1, char const *s2, char *ptr, int len)
{
	int	i;

	i = 0;
	while (s1[i] != '\0')
	{
		ptr[len] = s1[i];
		i++;
		len++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		ptr[len] = s2[i];
		i++;
		len++;
	}
	ptr[len] = '\0';
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	int		i;
	char	*ptr;

	len = 0;
	i = 0;
	ptr = NULL;
	while (s1[len] != '\0')
		len++;
	while (s2[i] != '\0')
	{
		len++;
		i++;
	}
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	len = 0;
	ptr = ft_joincpy(s1, s2, ptr, len);
	return (ptr);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*s1 = "abc";
// 	char	*s2 = "123";

// 	printf("%s", ft_strjoin(s1, s2));
// }