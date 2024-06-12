/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:25:19 by gstronge          #+#    #+#             */
/*   Updated: 2024/04/03 12:49:50 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_copy_str(char *buffer, char *str, int buff_strlen, int old_strlen)
{
	char	*newstr;
	int		i;

	newstr = NULL;
	i = 0;
	newstr = (char *)malloc((buff_strlen + old_strlen + 1) * sizeof(char));
	if (newstr == NULL)
	{
		if (str)
			free (str);
		return (NULL);
	}
	while (str && i < old_strlen)
	{
		newstr[i] = str[i];
		i++;
	}
	i = 0;
	while (i < buff_strlen)
	{
		newstr[old_strlen + i] = buffer[i];
		i++;
	}
	free (str);
	return (newstr);
}

int	ft_buffer_strlen(char *buffer, int buff_strlen)
{
	while (buffer[buff_strlen] != '\n' && buffer[buff_strlen] != '\0')
		buff_strlen++;
	if (buffer[buff_strlen] == '\n')
		buff_strlen++;
	return (buff_strlen);
}

char	*ft_make_str(char *buffer, char *str, int *bytes)
{
	int		buff_strlen;
	int		old_strlen;
	int		i;

	buff_strlen = 0;
	old_strlen = 0;
	i = 0;
	while (str && str[old_strlen] != '\0')
		old_strlen++;
	buff_strlen = ft_buffer_strlen(buffer, buff_strlen);
	str = ft_copy_str(buffer, str, buff_strlen, old_strlen);
	if (str == NULL)
		return (NULL);
	str[buff_strlen + old_strlen] = '\0';
	while (buffer[i + buff_strlen] != '\0')
	{
		buffer[i] = buffer[i + buff_strlen];
		i++;
	}
	if (i == 0)
		*bytes = 0;
	if (i == 0 && buff_strlen > 0 && str[old_strlen + buff_strlen - 1] == '\n')
		*bytes = -2;
	buffer[i] = '\0';
	return (str);
}

int	ft_make_buffer(int fd, char *buffer, char *str, int bytes)
{
	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes == -1)
	{
		if (str)
			free (str);
		return (-1);
	}
	if (bytes == 0)
		return (-2);
	buffer[bytes] = '\0';
	return (bytes);
}

int	ft_nl_str(char *str, int bytes)
{
	int	i;

	i = 0;
	if (bytes == -2)
		return (bytes);
	while (str && str[i] != '\0')
		i++;
	if (i != 0 && str[i - 1] == '\n')
		bytes = -3;
	return (bytes);
}
