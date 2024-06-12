/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:18:54 by gstronge          #+#    #+#             */
/*   Updated: 2024/03/15 11:26:03 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	**ft_free(char **strstr, int i)
{
	while (i >= 0)
	{
		free(strstr[i]);
		i--;
	}
	free(strstr);
	return (NULL);
}

static	int	ft_strnum(char const *s, char c, int strnum)
{
	int	i;

	i = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	if (s[i] == '\0')
		return (0);
	if (c == '\0' && i > 0)
		return (1);
	strnum = 1;
	while (s[i] != '\0')
	{
		if (s[i] == c && i != 0 && s[i - 1] != c)
			strnum++;
		if (s[i] == c && s[i + 1] == '\0')
			strnum--;
		i++;
	}
	return (strnum);
}

static	int	ft_copystr(char const *s, char c, char **strstr, int index)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
	}
	strstr[index] = (char *)malloc((i + 1) * sizeof(char));
	if (strstr[index] == NULL)
		return (i);
	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		strstr[index][i] = s[i];
		i++;
	}
	strstr[index][i] = '\0';
	return (i);
}

char	**ft_split(char const *s, char c)
{
	int		strnum;
	char	**strstr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	strnum = 0;
	strnum = ft_strnum(s, c, strnum);
	strstr = (char **)malloc((strnum + 1) * sizeof(char *));
	if (strstr == NULL)
		return (NULL);
	while (i < strnum)
	{
		while (s[j] == c)
			j++;
		j = j + ft_copystr(s + j, c, strstr, i);
		if (strstr[i] == NULL)
			return (ft_free(strstr, i));
		i++;
	}
	strstr[i] = NULL;
	return (strstr);
}

// #include <stdio.h>

// int	main()
// {
// 	char	*s = "t a  b ";
// 	char	c = ' ';
// 	char	**strstr;
// 	int		i = 0;

// 	strstr = ft_split(s, c);
// 	while (i < 4)
// 	{
// 		printf("main >%s< \n", strstr[i]);
// 		i++;
// 	}
// }