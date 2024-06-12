/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 23:54:29 by gstronge          #+#    #+#             */
/*   Updated: 2024/03/10 23:54:29 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_write_to_file(long num, int fd)
{
	size_t	bytes;
	char	temp;

	if (num > 0)
	{
		temp = (num % 10) + '0';
		ft_write_to_file(num / 10, fd);
		bytes = write(fd, &temp, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	size_t	bytes;
	long	num;

	num = n;
	if (num < 0)
	{
		num = -num;
		bytes = write(fd, "-", 1);
	}
	if (num == 0)
		bytes = write(fd, "0", 1);
	if (num > 0)
		ft_write_to_file(num, fd);
}

// #include <stdio.h>
// #include <fcntl.h>

// int	main(void)
// {
// 	int		n = 0;
// 	int		fd;

// 	fd = open("test.pdf", O_RDWR);

// 	ft_putnbr_fd(n, fd);
// }