/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:13:52 by gstronge          #+#    #+#             */
/*   Updated: 2024/06/12 18:52:59 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

void	ft_error(char *message, int error_no, t_map *grid)
{
	ft_free_all(grid);
	ft_putstr_fd(message, 1);
	ft_putstr_fd("\n", 1);
	exit(error_no);
}

void	ft_error_checks(int argc, char **argv)
{
	int		fd;
	char	buffer[1];
	t_map	*grid;
	int		i;

	grid = NULL;
	i = 0;
	if (argc != 2)
		ft_error("usage: ./executable filename.fdf", 22, grid);
	while (argv[1][i] != '.' && argv[1][i] != '\0')
		i++;
	if (ft_strncmp(&argv[1][i], ".fdf", 5))
		ft_error("file type must be .fdf", 22, grid);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error("file doesn't exist or can't be opened", errno, grid);
	if (read(fd, buffer, 1) <= 0)
	{
		close(fd);
		ft_error("file can't be read or is empty", errno, grid);
	}
	close(fd);
}

void	ft_free_all(t_map *grid)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	if (grid && grid->points)
	{
		while (row < grid->height)
		{
			while (grid->points[row] && col < grid->width)
			{
				if (grid->points[row][col].colour_pix)
					free(grid->points[row][col].colour_pix);
				col++;
			}
			if (grid->points[row])
				free(grid->points[row]);
			col = 0;
			row++;
		}
		free(grid->points);
	}
	if (grid)
		free(grid);
}

void	ft_free_split(char **map_array)
{
	int	i;

	i = 0;
	while (map_array[i] != NULL)
	{
		free(map_array[i]);
		i++;
	}
	free(map_array[i]);
	free(map_array);
}
