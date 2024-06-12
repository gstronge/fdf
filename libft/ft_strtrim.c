/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:07:58 by gstronge          #+#    #+#             */
/*   Updated: 2024/03/15 11:44:44 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_emptystr(char *ptr)
{
	ptr = (char *)malloc((1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ptr[0] = '\0';
	return (ptr);
}

static	size_t	ft_check_start(char const *s1, char const *set, size_t i)
{
	size_t	j;
	size_t	start;

	j = 0;
	start = 0;
	while (s1[i] != '\0')
	{
		while (set[j] != '\0')
		{
			if (set[j] == s1[i])
			{
				start++;
				break ;
			}
			j++;
		}
		if (set[j] == '\0')
			break ;
		i++;
		j = 0;
	}
	return (start);
}

static	size_t	ft_end(char const *s1, char const *set, size_t len, size_t i)
{
	size_t	j;
	size_t	end;

	j = 0;
	end = 0;
	while (i >= 0)
	{
		while (set[j] != '\0')
		{
			if (set[j] == s1[i])
			{
				end++;
				break ;
			}
			j++;
		}
		if (set[j] == '\0')
			break ;
		i--;
		j = 0;
	}
	return (len - end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	len;
	char	*ptr;

	i = 0;
	len = 0;
	ptr = NULL;
	start = ft_check_start(s1, set, i);
	while (s1[len] != '\0')
		len++;
	if (len == start)
		return (ft_emptystr(ptr));
	len = ft_end(s1, set, len, len - 1) - start;
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (i < len)
	{
		ptr[i] = s1[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*s1 = "";
// 	char	*set = "";

// 	printf(">%s<", ft_strtrim(s1, set));
// }