/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_points.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:20:48 by gstronge          #+#    #+#             */
/*   Updated: 2024/06/12 18:29:25 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

void	ft_parse_points(t_map *grid, int fd, char **split, int row)
{
	int	col;

	col = 0;
	grid->points[row] = (t_pixel *)malloc((grid->width) * sizeof(t_pixel));
	if (grid->points[row] == NULL)
	{
		close(fd);
		free(split);
		ft_error("malloc failed", errno, grid);
	}
	while (col < grid->width)
	{
		ft_fill_points(split, grid, row, col);
		ft_min_max(grid, row, col);
		col++;
	}
}

void	ft_fill_points(char **map_array, t_map *grid, int row, int col)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (map_array[col][i] != ',' && map_array[col][i] != '\0')
		i++;
	if (map_array[col][i] == '\0')
		grid->points[row][col].colour_pix = ft_strdup("FFFFFF");
	else
	{
		len = ft_strlen(&map_array[col][i + 3]);
		if (len == 6)
			grid->points[row][col].colour_pix = ft_strdup(&map_array[col][i \
					+ 3]);
		else
			ft_hex_to_str(grid, row, col, &map_array[col][i + 3]);
	}
	grid->points[row][col].z = ft_atoi(map_array[col]);
	ft_isometric(&(grid->points[row][col]), row, col);
}

void	ft_hex_to_str(t_map *grid, int row, int col, char *str)
{
	int	len;
	int	j;
	int	i;

	len = 0;
	j = 0;
	i = 0;
	len = ft_strlen(str);
	grid->points[row][col].colour_pix = (char *)malloc(7 * sizeof(char));
	if (grid->points[row][col].colour_pix == NULL)
		ft_error("malloc error", errno, grid);
	while (i < 6 - len)
	{
		grid->points[row][col].colour_pix[i] = '0';
		i++;
	}
	while (i < 6)
	{
		grid->points[row][col].colour_pix[i] = str[j];
		j++;
		i++;
	}
	grid->points[row][col].colour_pix[i] = '\0';
}

void	ft_isometric(t_pixel *pix, int row, int col)
{
	float	plan_x;
	float	plan_y;

	plan_x = col;
	plan_y = row;
	pix->x = (plan_x - plan_y) * cos(M_PI / 6);
	pix->y = (plan_x + plan_y) * sin(M_PI / 6) - pix->z;
}

void	ft_min_max(t_map *grid, int row, int col)
{
	if (grid->points[row][col].x > grid->max_x)
		grid->max_x = grid->points[row][col].x;
	if (grid->points[row][col].y > grid->max_y)
		grid->max_y = grid->points[row][col].y;
	if (grid->points[row][col].x < grid->min_x)
		grid->min_x = grid->points[row][col].x;
	if (grid->points[row][col].y < grid->min_y)
		grid->min_y = grid->points[row][col].y;
}
