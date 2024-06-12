/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:17:26 by gstronge          #+#    #+#             */
/*   Updated: 2024/06/12 18:21:53 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

t_map	*ft_make_grid(char **argv, t_map *grid, int32_t window_dims)
{
	char	*map_row;
	char	**split;

	map_row = NULL;
	split = NULL;
	grid = (t_map *)malloc(sizeof(t_map));
	if (grid == NULL)
		ft_error("malloc error", errno, grid);
	grid->points = NULL;
	grid->width = 0;
	grid->height = 0;
	grid->max_x = INT_MIN;
	grid->max_y = INT_MIN;
	grid->min_x = INT_MAX;
	grid->min_y = INT_MAX;
	grid->window_size = window_dims;
	ft_grid_size(argv, grid, map_row);
	ft_fill_grid(argv, grid, map_row, split);
	ft_scale(grid, grid->window_size - 100);
	return (grid);
}

void	ft_grid_size(char **argv, t_map *grid, char *map_row)
{
	int	fd;

	fd = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error("file can't be opened", errno, grid);
	map_row = get_next_line(fd);
	grid->width = ft_width_count(map_row);
	free(map_row);
	while (1)
	{
		grid->height++;
		map_row = get_next_line(fd);
		if (map_row == NULL)
			break ;
		if (ft_width_count(map_row) != grid->width)
		{
			free(map_row);
			close(fd);
			ft_error("incorrect map formatting", 22, grid);
		}
		free(map_row);
	}
	close(fd);
}

int	ft_width_count(char const *s)
{
	int	width;
	int	i;

	width = 0;
	i = 0;
	while (s[i] == ' ' && s[i] != '\0')
		i++;
	if (s[i] == '\0')
		return (0);
	while (s[i] != '\0' && s[i] != '\n')
	{
		if (s[i] != ' ')
		{
			width++;
			while (s[i] != ' ' && s[i] != '\0' && s[i] != '\n')
				i++;
		}
		else
		{
			while (s[i] == ' ')
				i++;
		}
	}
	return (width);
}

void	ft_fill_grid(char **argv, t_map *grid, char *map_row, char **split)
{
	int	fd;
	int	row;

	row = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error("file can't be opened", errno, grid);
	grid->points = (t_pixel **)malloc((grid->height) * sizeof(t_pixel *));
	if (grid->points == NULL)
	{
		close(fd);
		ft_error("malloc failed", errno, grid);
	}
	while (row < grid->height)
	{
		map_row = get_next_line(fd);
		split = ft_split(map_row, ' ');
		free(map_row);
		ft_parse_points(grid, fd, split, row);
		ft_free_split(split);
		row++;
	}
	close(fd);
}

void	ft_scale(t_map *grid, int32_t dims)
{
	int		row;
	int		col;
	float	offset;

	row = 0;
	col = 0;
	if (grid->max_x - grid->min_x > grid->max_y - grid->min_y)
		grid->scale = dims / (grid->max_x - grid->min_x);
	else
		grid->scale = dims / (grid->max_y - grid->min_y);
	while (row < grid->height)
	{
		while (col < grid->width)
		{
			offset = (dims - (grid->scale * (grid->max_x - grid->min_x))) / 2;
			grid->points[row][col].x = (grid->scale * (grid->points[row][col].x
						- grid->min_x)) + offset;
			offset = (dims - (grid->scale * (grid->max_y - grid->min_y))) / 2;
			grid->points[row][col].y = (grid->scale * (grid->points[row][col].y
						- grid->min_y)) + offset;
			col++;
		}
		row++;
		col = 0;
	}
}
