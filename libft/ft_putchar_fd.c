/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 23:21:31 by gstronge          #+#    #+#             */
/*   Updated: 2024/03/10 23:21:31 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	size_t	count;
	size_t	bytes;

	count = 1;
	bytes = write(fd, &c, count);
}

// #include <stdio.h>
// #include <fcntl.h>

// int	main(void)
// {
// 	char	c = 'a';
// 	int		fd;

// 	fd = open("test.pdf", O_RDWR);

// 	ft_putchar_fd(c, fd);
// }