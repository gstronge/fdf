/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_calcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:35:50 by gstronge          #+#    #+#             */
/*   Updated: 2024/06/12 18:45:52 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

t_line_pix	ft_make_line(t_map *grid, int row, int col, char row_or_col)
{
	t_line_pix	line;

	if (row_or_col == 'c')
	{
		line.r_or_c = 'c';
		line.x = round(grid->points[row][col - 1].x);
		line.y = round(grid->points[row][col - 1].y);
		line.dx = round(grid->points[row][col].x) - \
				round(grid->points[row][col - 1].x);
		line.dy = round(grid->points[row][col].y) - \
				round(grid->points[row][col - 1].y);
	}
	if (row_or_col == 'r')
	{
		line.r_or_c = 'r';
		line.x = round(grid->points[row][col].x);
		line.y = round(grid->points[row][col].y);
		line.dx = round(grid->points[row - 1][col].x) - \
				round(grid->points[row][col].x);
		line.dy = round(grid->points[row - 1][col].y) - \
				round(grid->points[row][col].y);
	}
	line.f = 0;
	line.colour = ft_line_colour(grid, row, col, line);
	return (line);
}

void	ft_up_xg(t_line_pix line, int end, mlx_image_t *img)
{
	line.f = line.dx / 2;
	while (round(line.x) + 1 < end)
	{
		line.x++;
		line.f = line.f + line.dy;
		if (line.f <= 0)
		{
			line.f = line.f + line.dx;
			line.y--;
		}
		mlx_put_pixel(img, round(line.x), round(line.y), line.colour);
	}
}

void	ft_up_yg(t_line_pix line, int end, mlx_image_t *img)
{
	line.f = -line.dy / 2;
	while (round(line.y) - 1 > end)
	{
		line.y--;
		line.f = line.f - line.dx;
		if (line.f <= 0)
		{
			line.f = line.f - line.dy;
			line.x++;
		}
		mlx_put_pixel(img, round(line.x), round(line.y), line.colour);
	}
}

void	ft_down_xg(t_line_pix line, int end, mlx_image_t *img)
{
	line.f = line.dx / 2;
	while (round(line.x) + 1 < end)
	{
		line.x++;
		line.f = line.f - line.dy;
		if (line.f <= 0)
		{
			line.f = line.f + line.dx;
			line.y++;
		}
		mlx_put_pixel(img, round(line.x), round(line.y), line.colour);
	}
}

void	ft_down_yg(t_line_pix line, int end, mlx_image_t *img)
{
	line.f = line.dy / 2;
	while (round(line.y) + 1 < end)
	{
		line.y++;
		line.f = line.f - line.dx;
		if (line.f <= 0)
		{
			line.f = line.f + line.dy;
			line.x++;
		}
		mlx_put_pixel(img, round(line.x), round(line.y), line.colour);
	}
}
