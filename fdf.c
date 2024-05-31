/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:04:10 by gstronge          #+#    #+#             */
/*   Updated: 2024/05/31 19:55:19 by gstronge         ###   ########.fr       */
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


pixel	*ft_isometric(pixel *pix, int row, int col)
{
	pix->x = (sqrt(2)/2) * (col - row);//need to remove the sqrt function!!!!!!!!!!!
	pix->y = ((sqrt(6)/6) * (col + row)) - ((sqrt(3)/3) * pix->z);//need to remove the sqrt function!
	return (pix);
}

uint32_t	ft_colour(char *str)
{
	uint32_t	colour;
	int			i;

	colour = 0;
	i = 0;
	while (i < 6 && str[i] != '\0')
	{
		if (str[i] <= '9')
			colour = (colour * 16) + str[i] - '0';
		else if (str[i] <= 'F' && str[i] >= 'A')
			colour = (colour * 16) + str[i] - 'A' + 10;
			else if (str[i] <= 'f' && str[i] >= 'a')
			colour = (colour * 16) + str[i] - 'a' + 10;
		i++;	
	}
	while (i < 8)
	{
		colour = colour << 4;
		i++;
	}
	colour += 255;
	return (colour);
}

void	ft_fill_points(char **map_array, pixel *pix, int row, int col)
{
	int		i;

	i = 0;
	while (map_array[col][i] != ',' && map_array[col][i] != '\0')
		i++;
	if (map_array[col][i] == '\0')
		pix->colour = 0xFFFFFFFF;
	else
		pix->colour = ft_colour(&map_array[col][i + 3]);
	pix->z = ft_atoi(map_array[col]);
	pix = ft_isometric(pix, row, col);
}

void	ft_min_max(map_grid *grid, int row, int col)
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

void	ft_free_split(char **map_array, int i)
{
	while (map_array[i] != NULL)
	{
		free(map_array[i]);
		i++;
	}
	free(map_array[i]);
	free(map_array);
}

map_grid	*ft_fill_grid(char **argv, map_grid *grid)
{
	int		fd;
	char	*map_line;
	char	**map_array;
	int 	row;
	int 	col;

	map_line = NULL;
	map_array = NULL;
	row = 0;
	col = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (NULL);
		//error_free();
	grid->points = (pixel **)malloc((grid->height + 1) * sizeof(pixel *));
	if (grid->points == NULL)
		return (NULL);
		//error_free();
	while (row < grid->height)
	{
		map_line = get_next_line(fd);
		map_array = ft_split(map_line, ' ');
		if (grid->points == NULL)
			return (NULL);
			//error_free();
		grid->points[row] = (pixel *)malloc((grid->width + 1) * sizeof(pixel));
		while (col < grid->width)
		{
			ft_fill_points(map_array, &grid->points[row][col] , row, col);
			ft_min_max(grid, row, col);
			col++;
		}
		row++;
		col = 0;
		free(map_line);
		ft_free_split(map_array, 0);
	}
	grid->points[row] = NULL;
	close(fd);
	return (grid);
}

int	ft_width_count(char const *s, int width)
{
	int	i;

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

map_grid	*ft_grid_size(char **argv, map_grid *grid)
{
	int		fd;
	char	*map_line;
	
	fd = 0;
	map_line = NULL;
	grid->height = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (NULL);
	map_line = get_next_line(fd);
	grid->width = ft_width_count(map_line, 0);
	free(map_line);
	while (1)
	{
		grid->height++;
		map_line = get_next_line(fd);
		if (map_line == NULL)
			break;
		// printf("%d, %d\n", ft_width_count(map_line, 0), grid->height);
		// if (ft_width_count(map_line, 0) != grid->width)
		// {
		// 	perror("===================== map is incorrectly formatted ========================");//pylone
		// 	exit(EXIT_FAILURE);
		// }
		free(map_line);
	}
	close(fd);
	return (grid);
}

void	ft_scale(map_grid *grid, int32_t img_dim)
{
	int		row;
	int		col;
	float	offset;

	row = 0;
	col = 0;
	if (grid->max_x - grid->min_x > grid->max_y - grid->min_y)
		grid->scale = (img_dim - 100) / (grid->max_x - grid->min_x);
	else
		grid->scale = (img_dim - 100) / (grid->max_y - grid->min_y);
	while (row < grid->height)
	{
		while (col < grid->width)
		{
			offset = (img_dim - 100 - (grid->scale * (grid->max_x - grid->min_x))) / 2;
			grid->points[row][col].x = (grid->scale * (grid->points[row][col].x - grid->min_x)) + offset;
			offset = (img_dim - 100 - (grid->scale * (grid->max_y - grid->min_y))) / 2;
			grid->points[row][col].y = (grid->scale * (grid->points[row][col].y - grid->min_y)) + offset;
			col++;
		}
		row++;
		col = 0;
	}
}

map_grid	*ft_make_grid(char **argv, map_grid *grid, int32_t img_dim)
{
	grid = (map_grid *)malloc(sizeof(map_grid));
	if (grid == NULL)
		exit(EXIT_FAILURE);
	grid->max_x = FLT_MIN;
	grid->max_y = FLT_MIN;
	grid->min_x = FLT_MAX;	
	grid->min_y = FLT_MAX;	
	grid = ft_grid_size(argv, grid);
	grid = ft_fill_grid(argv, grid);
	ft_scale(grid, img_dim);

	if (grid == NULL)
		exit (EXIT_FAILURE);
	return (grid);
}

uint32_t ft_line_colour(map_grid *grid, int row, int col, line_pixel line)
{
	if (line.r_or_c == 'r')
	{
		if (grid->points[row][col].colour == grid->points[row - 1][col].colour)
			return (grid->points[row][col].colour);
		if (grid->points[row][col].colour == 0xFFFFFFFF)
			return (grid->points[row - 1][col].colour);
		if (grid->points[row - 1][col].colour == 0xFFFFFFFF)
			return (grid->points[row][col].colour);
	}
	else if (line.r_or_c == 'c')
	{
		if (grid->points[row][col].colour == grid->points[row][col - 1].colour)
			return (grid->points[row][col].colour);
		if (grid->points[row][col].colour == 0xFFFFFFFF)
			return (grid->points[row][col - 1].colour);
		if (grid->points[row][col - 1].colour == 0xFFFFFFFF)
			return (grid->points[row][col].colour);
	}
	return(0xFFFFFFFF);
}

line_pixel	ft_make_line(map_grid *grid, int row, int col, char row_or_col)
{
	line_pixel line;
	
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

void	ft_up_xg(line_pixel line, int end, mlx_image_t *img)
{
	line.f = line.dx / 2;
	while (line.x + 1 < end)
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

void	ft_up_yg(line_pixel line, int end, mlx_image_t *img)
{
	line.f = -line.dy / 2;
	while (line.y - 1 > end)
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

void	ft_down_xg(line_pixel line, int end, mlx_image_t *img)
{
	line.f = line.dx / 2;
	while (line.x + 1 < end)
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

void	ft_down_yg(line_pixel line, int end, mlx_image_t *img)
{
	line.f = line.dy / 2;
	while (line.y + 1 < end)
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
		
void	ft_draw_line(map_grid *grid, int row, int col, mlx_image_t *img)
{
	line_pixel	line;
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

void	ft_error_checks(int argc, char **argv)
{
	int		fd;
	char	buffer[5];
	int	i;

	i = 0;
	if (argc != 2)// ================== print error messages on ALL ======================
		exit(EXIT_FAILURE);
	while (argv[1][i] != '.' && argv[1][i] != '\0')
		i++;
	if (ft_strncmp(&argv[1][i], ".fdf", 5))
	{
		errno = 22;
		perror("must be a .fdf file");
		exit(EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("file can't be opened");
		exit(EXIT_FAILURE);
	}
	if (read(fd, buffer, 5) <= 0)
	{
		perror("file can't be read");
		close(fd);
		exit(EXIT_FAILURE);	
	}
	close(fd);
}

void	ft_free_all(map_grid *grid, int row)
{
	while (row < grid->height)
	{
		if (grid->points[row])
			free(grid->points[row]);
		row++;
	}
	if (grid->points)
		free(grid->points);
	if (grid)
		free(grid);
}


void	keypress(mlx_key_data_t keydata, void *param)
{
	map_grid   *grid;
	
    grid = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(grid->mlx);
	}
}

static void ft_error(map_grid *grid)
{
	if (grid)
		ft_free_all(grid, 0);
	perror(mlx_strerror(mlx_errno));// is this correct ======================================
}

void	ft_make_image(map_grid *grid, int img_dim)
{
	int	row;
	int	col;
	
	row = 0;
	col = 0;
	grid->img = mlx_new_image(grid->mlx, img_dim, img_dim);
	if (!grid->img)
		ft_error(grid);
	while (row < grid->height)
	{
		while (col < grid->width)
		{
			if (grid->points[row][col].x >= 0 && grid->points[row][col].x <= img_dim && grid->points[row][col].y >= 0 && grid->points[row][col].y <= img_dim)
				mlx_put_pixel(grid->img, round(grid->points[row][col].x), round(grid->points[row][col].y), grid->points[row][col].colour);
			ft_draw_line(grid, row, col, grid->img);
			col++;
		}
		row++;
		col = 0;
	}
}

// void	leaks(void)
// {
// 	system("leaks fdf");
// }

int32_t	main(int argc, char **argv)
{
	map_grid	*grid;
	int			img_dim;

	grid = NULL;
	img_dim = 1200;
	ft_error_checks(argc, argv);
	grid = ft_make_grid(argv, grid, img_dim);
	mlx_set_setting(MLX_MAXIMIZED, false);
	grid->mlx = mlx_init(img_dim, img_dim, "FDF - MAP", true);
	if (!grid->mlx)
		ft_error(grid);
	ft_make_image(grid, img_dim);
	if (mlx_image_to_window(grid->mlx, grid->img, 50, 50) < 0)
		ft_error(grid);
	mlx_key_hook(grid->mlx, keypress, grid);
	mlx_loop(grid->mlx);
	mlx_terminate(grid->mlx);
	ft_free_all(grid, 0);
	return (EXIT_SUCCESS);
}
