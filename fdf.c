/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:04:10 by gstronge          #+#    #+#             */
/*   Updated: 2024/06/11 20:10:19 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "MLX42/MLX42.h"
#include "fdf.h"

/*

TO FIX
======
pixels not lining up!
leaks!!!!!!!!!!!!

ALLOWED
=======
• open, close, read, write, malloc, free, perror, strerror, exit
• All functions of the math library (-lm compiler option, man man 3 math)

ft_make_grid > dimensions of grid, 2D array of points
ft_parse_map > fill out points structs in the grid, then iso and simultaneously find min/max x and y
ft_draw_points > after scaling has been done based on min/max x and y 
(need to figure out how to center also!!!!????)
ft_calculate_(and maybe draw)lines > Bresenham https://www.youtube.com/watch?v=vlZFSzCIwoc
free (including split and gnl)

error handling
==============
no of args, map doesn't exist in location,  other?? (don't need to check if map is incorrect??? from subject - we assume the map contained in the file is properly formatted.)

make a grid:
============

need a grid to include width and height of map and also the max/min x and y values after the isometric conversion is done to be able to scale
also need a 2D array or linked list (with x/y coords of map) to be able to draw the lines

parse map:
==========
need to do colours
scaling issue???????????

then add lines between pixels - how to do this?

isometric view:
===============
from Wiki: An isometric view of an object can be obtained by choosing the viewing direction such that the angles between the projections of the x, y, and z axes are all the same, or 120°. For example, with a cube, this is done by first looking straight towards one face. Next, the cube is rotated ±45° about the vertical axis, followed by a rotation of approximately 35.264° (precisely arcsin 1⁄√3 or arctan 1⁄√2, which is related to the Magic angle) about the horizontal axis. 

|x'| = x*cos(angle) - y*cos(angle)
|y'| = x*sin(angle) + y*cos(angle)

use this to rotate 45 deg. in the x/y plane
then rotate approximately 35.264° (precisely arcsin 1⁄√3 or arctan 1⁄√2)
int the y/z plane

x' = (x−z) * cos(30)
y' = y+(x+z) * sin(30)

x' = (sqrt(2)/2) * (x - y);
y' = ((sqrt(6)/6) * (x + y)) - ((sqrt(3)/3) * z);

*/

// /*
//  * An image instance can be summarized as just a simple
//  * x, y & z coordinate.
//  * 
//  * Coordinates start from the top left of the screen at 0,0 and increase
//  * towards the bottom right.
//  * 
//  * NOTE: To change the z value, use mlx_set_instance_depth!
//  * 
//  * @param x The x location.
//  * @param y The y location.
//  * @param z The z depth, controls if the image is on the fore or background.
//  * @param enabled If true, the instance is drawn, else it's not.
//  */
// typedef struct mlx_instance
// {
// 	int32_t	x;
// 	int32_t	y;
// 	int32_t	z;
// 	bool	enabled;
// }	mlx_instance_t;

// /*
//  * Sets the depth / Z axis value of an instance.
//  * 
//  * NOTE: Keep in mind that images that are on the same Z layer cut each other off.
//  * so if you don't see your image anymore make sure it's not conflicting by being on
//  * the same layer as another image.
//  * 
//  * @param[in] instance The instance on which to change the depth.
//  * @param[in] zdepth The new depth value.
// */
// void mlx_set_instance_depth(mlx_instance_t* instance, int32_t zdepth);


#include <stdio.h>// --------- REMOVE ----------- REMOVE ----------- REMOVE ----------- 

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

void	ft_error_found(const char *message, int error_no, t_map *grid)
{
	ft_free_all(grid);
	errno = error_no;
	perror(message);
	exit(errno);
}

void	ft_error_checks(int argc, char **argv)
{
	int			fd;
	char		buffer[1];
	t_map	*grid;
	int			i;

	grid = NULL;
	i = 0;
	if (argc != 2)
		ft_error_found("usage: ./executable \"filename.fdf\"", 22, grid);
	while (argv[1][i] != '.' && argv[1][i] != '\0')
		i++;
	if (ft_strncmp(&argv[1][i], ".fdf", 5))
		ft_error_found("file type must be .fdf", 22, grid);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error_found("file can't be opened", errno, grid);
	if (read(fd, buffer, 1) <= 0)
	{
		close(fd);
		ft_error_found("file can't be read or is empty", errno, grid);
	}
	close(fd);
}

void	ft_isometric(t_pixel *pix, int row, int col)
{
	float	plan_x = col;
	float	plan_y = row;

	pix->x = (plan_x - plan_y) * cos(M_PI / 6);// =========== cos(30 deg) =============
	pix->y = (plan_x + plan_y) * sin(M_PI / 6) - pix->z;// ========== sin(30 deg) ===========
}

uint32_t	ft_hex_to_int(char *str)
{
	uint32_t	colour;
	int			i;

	colour = 0;
	i = 0;
	while (i < 6 && str[i] != '\0')
	{
		if (str[i] <= '9' && str[i] >= '0' )
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

void	ft_hex_to_str(t_map *grid, int row, int col, char* str)
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
		ft_error_found("malloc error", errno, grid);
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
			grid->points[row][col].colour_pix = ft_strdup(&map_array[col][i + 3]);
		else 
			ft_hex_to_str(grid, row, col, &map_array[col][i + 3]);
	}
	grid->points[row][col].z = ft_atoi(map_array[col]);
	ft_isometric(&(grid->points[row][col]), row, col);
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

void	ft_parse_points(t_map *grid, int fd, char ** split, int row)
{
	int	col;

	col = 0;
	grid->points[row] = (t_pixel *)malloc((grid->width) * sizeof(t_pixel));
	if (grid->points[row] == NULL)
	{
		close(fd);
		free(split);
		ft_error_found("malloc failed", errno, grid);
	}
	while (col < grid->width)
	{
		ft_fill_points(split, grid, row, col);
		ft_min_max(grid, row, col);
		col++;
	}	
}

void	ft_fill_grid(char **argv, t_map *grid, char *map_row, char **split)
{
	int		fd;
	int 	row;

	row = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error_found("file can't be opened", errno, grid);
	grid->points = (t_pixel **)malloc((grid->height) * sizeof(t_pixel *));
	if (grid->points == NULL)
	{
		close(fd);
		ft_error_found("malloc failed", errno, grid);
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

int	ft_width_count(char const *s)
{
	int width;
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

void	ft_grid_size(char **argv, t_map *grid, char *map_row)
{
	int		fd;
	
	fd = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error_found("file can't be opened", errno, grid);
	map_row = get_next_line(fd);
	grid->width = ft_width_count(map_row);
	free(map_row);
	while (1)
	{
		grid->height++;
		map_row = get_next_line(fd);
		if (map_row == NULL)
			break;
		if (ft_width_count(map_row) != grid->width)
		{
			free(map_row);
			close(fd);
			ft_error_found("incorrect map formatting", 22, grid);
		}
		free(map_row);
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
			grid->points[row][col].x = (grid->scale * (grid->points[row][col].x - grid->min_x)) + offset;
			offset = (dims - (grid->scale * (grid->max_y - grid->min_y))) / 2;
			grid->points[row][col].y = (grid->scale * (grid->points[row][col].y - grid->min_y)) + offset;
			col++;
		}
		row++;
		col = 0;
	}
}

t_map	*ft_make_grid(char **argv, t_map *grid, int32_t window_size)
{
	char	*map_row;
	char	**split;

	map_row = NULL;
	split = NULL;
	grid = (t_map *)malloc(sizeof(t_map));
	if (grid == NULL)
		exit(errno);
	grid->points = NULL;
	grid->width = 0;
	grid->height = 0;
	grid->max_x = FLT_MIN;
	grid->max_y = FLT_MIN;
	grid->min_x = FLT_MAX;
	grid->min_y = FLT_MAX;
	ft_grid_size(argv, grid, map_row);
	ft_fill_grid(argv, grid, map_row, split);
	ft_scale(grid, window_size - 100);
	return (grid);
}


char	*ft_make_byte(t_map *grid, char *str, char *byte)
{
	if (byte == NULL)
	{		
		byte = (char *)malloc(3 * sizeof(char));
		if (byte == NULL)
		{
			free(byte);
			ft_error_found("malloc error", errno, grid);
		}
	}
	byte[0] = '\0';
	byte[1] = '\0';
	byte[2] = '\0';
	if (str[0])
		byte[0] = str[0];
	if (str[1])
		byte[1] = str[1];
	return(byte);
}

uint32_t	ft_rgb_to_int(char *str)
{
	uint32_t	colour;
	int			i;

	colour = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] <= '9' && str[i] >= '0' )
			colour = (colour * 16) + str[i] - '0';
		else if (str[i] <= 'F' && str[i] >= 'A')
			colour = (colour * 16) + str[i] - 'A' + 10;
		else if (str[i] <= 'f' && str[i] >= 'a')
			colour = (colour * 16) + str[i] - 'a' + 10;
		i++;	
	}
	return (colour);
}

uint32_t	ft_av_colour(t_map *grid, char *clr_a, char *clr_b, uint32_t av_clr)
{
	char	*byte_a;
	char	*byte_b;
	int		i;

	i = 0;
	byte_a = NULL;
	byte_b = NULL;
	while (i < 6 && (clr_a[i] != '\0' || clr_b[i] != '\0'))
	{
		byte_a = ft_make_byte(grid, &clr_a[i], byte_a);
		byte_b = ft_make_byte(grid, &clr_b[i], byte_b);
		av_clr = av_clr << 8 | (ft_rgb_to_int(byte_a) + ft_rgb_to_int(byte_b))/2;
		i += 2;
	}
	av_clr = av_clr << 8;
	av_clr += 255;
	free(byte_a);
	free(byte_b);
	return (av_clr);
}

uint32_t ft_line_colour(t_map *grid, int row, int col, t_line_pixel line)
{
	uint32_t	colour;

	colour = 0;
	if (line.r_or_c == 'r')
	{
		if (!ft_strncmp(grid->points[row][col].colour_pix, grid->points[row - 1][col].colour_pix, 8))
			colour = ft_hex_to_int(grid->points[row][col].colour_pix);
		else
			colour = ft_av_colour(grid, grid->points[row][col].colour_pix, grid->points[row - 1][col].colour_pix, colour);
	}
	else if (line.r_or_c == 'c')
	{
		if (!ft_strncmp(grid->points[row][col].colour_pix, grid->points[row][col - 1].colour_pix, 8))
			colour = ft_hex_to_int(grid->points[row][col].colour_pix);
		else
			colour = ft_av_colour(grid, grid->points[row][col].colour_pix, grid->points[row][col - 1].colour_pix, colour);
	}
	return(colour);
}

t_line_pixel	ft_make_line(t_map *grid, int row, int col, char row_or_col)
{
	t_line_pixel line;
	
	if (row_or_col == 'c')
	{
		line.x = round(grid->points[row][col - 1].x);
		line.y = round(grid->points[row][col - 1].y);
		line.dx = round(grid->points[row][col].x) - round(grid->points[row][col - 1].x);
		line.dy = round(grid->points[row][col].y) - round(grid->points[row][col - 1].y);
		line.r_or_c = 'c';
	}
	if (row_or_col == 'r')
	{
		line.x = round(grid->points[row][col].x);
		line.y = round(grid->points[row][col].y);
		line.dx = round(grid->points[row - 1][col].x) - round(grid->points[row][col].x);
		line.dy = round(grid->points[row - 1][col].y) - round(grid->points[row][col].y);
		line.r_or_c = 'r';
	}
	line.f = 0;
	line.colour = ft_line_colour(grid, row, col, line);
	return (line);
}

void	ft_up_xg(t_line_pixel line, int end, mlx_image_t *img)
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

void	ft_up_yg(t_line_pixel line, int end, mlx_image_t *img)
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

void	ft_down_xg(t_line_pixel line, int end, mlx_image_t *img)
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

void	ft_down_yg(t_line_pixel line, int end, mlx_image_t *img)
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
		
void	ft_draw_line(t_map *grid, int row, int col, mlx_image_t *img)
{
	t_line_pixel	line;
	if (col > 0)
	{
		line = ft_make_line(grid, row, col, 'c');
		if (line.dy <= 0 && line.dx > (-1 * line.dy))
			ft_up_xg(line, round(grid->points[row][col].x), img);
		else if (line.dy <= 0 && line.dx < (-1 * line.dy))
			ft_up_yg(line, round(grid->points[row][col].y), img);
		else if (line.dx > line.dy)
			ft_down_xg(line, round(grid->points[row][col].x), img);
		else
			ft_down_yg(line, round(grid->points[row][col].y), img);
	}
	if (row > 0)
	{
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
}

void	ft_make_image(t_map *grid, int window_size)
{
	uint32_t	colour;
	int			row;
	int			col;

	colour = 0;
	row = 0;
	col = 0;
	grid->img = mlx_new_image(grid->mlx, window_size, window_size);
	if (!grid->img)
		ft_error_found("error creating image", errno, grid);
	while (row < grid->height)
	{
		while (col < grid->width)
		{
			colour = ft_hex_to_int(grid->points[row][col].colour_pix);
			if (grid->points[row][col].x >= 0 && grid->points[row][col].x <= window_size && grid->points[row][col].y >= 0 && grid->points[row][col].y <= window_size)
				mlx_put_pixel(grid->img, round(grid->points[row][col].x), round(grid->points[row][col].y), colour);
			ft_draw_line(grid, row, col, grid->img);
			col++;
		}
		row++;
		col = 0;
	}
}

// void	ft_scale(t_map *grid, float scale_adj)
// {
	
// }

void	ft_transform(t_map *grid, char direction, int row, int col)
{
	if (direction == 'u')
		grid->points[row][col].y -= 10;
	if (direction == 'd')
		grid->points[row][col].y += 10;
	if (direction == 'l')
		grid->points[row][col].x -= 10;
	if (direction == 'r')
		grid->points[row][col].x += 10;
}

void	ft_transform_image(t_map *grid, int window_size, char direction)
{
	uint32_t	colour;
	int			row;
	int			col;

	colour = 0;
	row = 0;
	col = 0;
	grid->img = mlx_new_image(grid->mlx, window_size, window_size);
	if (!grid->img)
		ft_error_found("error creating image", errno, grid);
	while (row < grid->height)
	{
		while (col < grid->width)
		{
			ft_transform(grid, direction, row, col);
			colour = ft_hex_to_int(grid->points[row][col].colour_pix);
			if (grid->points[row][col].x >= 0 && grid->points[row][col].x < window_size && grid->points[row][col].y >= 0 && grid->points[row][col].y < window_size)
			{
				mlx_put_pixel(grid->img, round(grid->points[row][col].x), round(grid->points[row][col].y), colour);
				ft_draw_line(grid, row, col, grid->img);
			}
			col++;
		}
		row++;
		col = 0;
	}
	if (mlx_image_to_window(grid->mlx, grid->img, 50, 50) < 0)
		ft_error_found("error adding image to window", errno, grid);
}

void	keypress(mlx_key_data_t keydata, void *param)
{
	t_map   *grid;
	int		row;
	int		col;

	row = 0;
	col = 0;
    grid = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(grid->mlx);
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
	{
		mlx_delete_image(grid->mlx, grid->img);
		ft_transform_image(grid, 1200, 'u');
	}
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
	{
		mlx_delete_image(grid->mlx, grid->img);
		ft_transform_image(grid, 1200, 'd');
	}
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
	{
		mlx_delete_image(grid->mlx, grid->img);
		ft_transform_image(grid, 1200, 'r');
	}
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
	{
		mlx_delete_image(grid->mlx, grid->img);
		ft_transform_image(grid, 1200, 'l');
	}
	// if (keydata.key == MLX_KEY_PAGE_UP && keydata.action == MLX_PRESS)
	// 	ft_scale(grid, 1.1);
}

// static void ft_error(t_map *grid)//maybe remove this function and just use the other one --------------------------
// {
// 	if (grid)
// 		ft_free_all(grid);
// 	perror(mlx_strerror(mlx_errno));// is this correct ======================================
// }

void	leaks(void)// ----------------------------- REMOVE ---------------------------------
{
	system("leaks fdf");
}// ----------------------------- REMOVE --------------------------------- ---------------


int32_t	main(int argc, char **argv)
{
	t_map	*grid;
	int			window_size;

	grid = NULL;
	window_size = 1200;
	atexit(leaks);// ----------------------------- REMOVE ---------------------------------
	ft_error_checks(argc, argv);
	grid = ft_make_grid(argv, grid, window_size);
	mlx_set_setting(MLX_MAXIMIZED, false);
	grid->mlx = mlx_init(window_size, window_size, "FDF - MAP", false);
	if (!grid->mlx)
		ft_error_found("error initialising mlx", errno, grid);
	ft_make_image(grid, window_size);
	if (mlx_image_to_window(grid->mlx, grid->img, 50, 50) < 0)
		ft_error_found("error adding image to window", errno, grid);
	mlx_key_hook(grid->mlx, keypress, grid);
	mlx_loop(grid->mlx);
	mlx_terminate(grid->mlx);
	ft_free_all(grid);
	return (EXIT_SUCCESS);
}
