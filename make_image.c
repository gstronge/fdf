/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:39:53 by gstronge          #+#    #+#             */
/*   Updated: 2024/06/12 18:58:00 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

void	ft_draw_line_col(t_map *grid, int row, int col, mlx_image_t *img)
{
	t_line_pix	line;

	line = ft_make_line(grid, row, col, 'c');
	if (line.dy < 0 && line.dx > (-1 * line.dy))
		ft_up_xg(line, round(grid->points[row][col].x), img);
	else if (line.dy < 0 && line.dx < (-1 * line.dy))
		ft_up_yg(line, round(grid->points[row][col].y), img);
	else if (line.dx > line.dy)
		ft_down_xg(line, round(grid->points[row][col].x), img);
	else
		ft_down_yg(line, round(grid->points[row][col].y), img);
}

void	ft_draw_line_row(t_map *grid, int row, int col, mlx_image_t *img)
{
	t_line_pix	line;

	line = ft_make_line(grid, row, col, 'r');
	if (line.dy < 0 && line.dx > (-1 * line.dy))
		ft_up_xg(line, round(grid->points[row - 1][col].x), img);
	else if (line.dy < 0 && line.dx < (-1 * line.dy))
		ft_up_yg(line, round(grid->points[row - 1][col].y), img);
	else if (line.dx > line.dy)
		ft_down_xg(line, round(grid->points[row - 1][col].x), img);
	else
		ft_down_yg(line, round(grid->points[row - 1][col].y), img);
}

uint32_t	ft_hex_to_int(char *str)
{
	uint32_t	colour;
	int			i;

	colour = 0;
	i = 0;
	while (i < 6 && str[i] != '\0')
	{
		if (str[i] <= '9' && str[i] >= '0')
			colour = (colour * 16) + str[i] - '0';
		else if (str[i] <= 'F' && str[i] >= 'A')
			colour = (colour * 16) + str[i] - 'A' + 10;
		else if (str[i] <= 'f' && str[i] >= 'a')
			colour = (colour * 16) + str[i] - 'a' + 10;
		i++;
	}
	colour = colour << 8;
	colour += 255;
	return (colour);
}

void	ft_draw_pix_on_img(t_map *grid, t_pixel *pix, int32_t window_size)
{
	uint32_t	colour;

	colour = 0;
	colour = ft_hex_to_int(pix->colour_pix);
	if (pix->x >= 0 && pix->x < window_size && pix->y >= 0 \
			&& pix->y < window_size)
		mlx_put_pixel(grid->img, round(pix->x), round(pix->y), colour);
}

void	ft_draw_image(t_map *grid, int32_t window_size)
{
	int			row;
	int			col;

	row = 0;
	col = 0;
	grid->img = mlx_new_image(grid->mlx, window_size, window_size);
	if (!grid->img)
		ft_error("error creating image", errno, grid);
	while (row < grid->height)
	{
		while (col < grid->width)
		{
			ft_draw_pix_on_img(grid, &(grid->points[row][col]), window_size);
			if (col > 0)
				ft_draw_line_col(grid, row, col, grid->img);
			if (row > 0)
				ft_draw_line_row(grid, row, col, grid->img);
			col++;
		}
		row++;
		col = 0;
	}
}
