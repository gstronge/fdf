/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:04:10 by gstronge          #+#    #+#             */
/*   Updated: 2024/05/29 19:09:36 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "MLX42/MLX42.h"
#include "fdf.h"

/*


PLAN:
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
#include <math.h>// --------- REMOVE ----------- REMOVE ----------- REMOVE ----------- 


static void ft_error(void)
{
	mlx_strerror(mlx_errno);
	exit(EXIT_FAILURE);
}

point	*ft_isometric(point *pixel, int row, int column)
{
	pixel->x = (sqrt(2)/2) * (column - row);//need to remove the sqrt function!!!!!!!!!!!
	pixel->y = ((sqrt(6)/6) * (column + row)) - ((sqrt(3)/3) * pixel->z);//need to remove the sqrt function!
	return (pixel);
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
		else
			colour = (colour * 16) + str[i] - 'A' + 10;
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

// point	*ft_make_point(char **map_array, int x_coord, int y_coord, int scale)
// {
// 	point	*pixel;
// 	int		i;

// 	i = 0;
// 	pixel = (point *)malloc(sizeof(point));
// 	while (map_array[x_coord][i] != ',' && map_array[x_coord][i] != '\0')
// 		i++;
// 	if (map_array[x_coord][i] == '\0')
// 		pixel->colour = 0xFFFFFFFF;
// 	else
// 		pixel->colour = ft_colour(&map_array[x_coord][i + 3]);
// 	// printf(" z = %f colour after = %x\n",pixel->z, pixel->colour);//=============================================
// 	pixel->x = (x_coord * scale) + 500;
// 	pixel->y = (y_coord * scale) + 200;
// 	pixel->z = ft_atoi(map_array[x_coord]) * scale;
// 	pixel = ft_isometric(pixel);
// 	// printf(" z = %f colour before = %x ",pixel->z, pixel->colour);//=============================================
// 	return(pixel);
// }

void	ft_fill_points(char **map_array, point *pixel, int row, int column)
{
	int		i;

	i = 0;
	while (map_array[column][i] != ',' && map_array[column][i] != '\0')
		i++;
	if (map_array[column][i] == '\0')
		pixel->colour = 0xFFFFFFFF;
	else
		pixel->colour = ft_colour(&map_array[column][i + 3]);
	// printf(" z = %f colour after = %x\n",pixel->z, pixel->colour);//=============================================
	pixel->z = ft_atoi(map_array[column]);
	pixel = ft_isometric(pixel, row, column);
	// printf(" z = %f colour before = %x ",pixel->z, pixel->colour);//=============================================
}

void	ft_min_max(map_grid *grid, int row, int column)
{
	if (grid->point_grid[row][column].x > grid->max_x)
		grid->max_x = grid->point_grid[row][column].x;
	if (grid->point_grid[row][column].y > grid->max_y)
		grid->max_y = grid->point_grid[row][column].y;
	if (grid->point_grid[row][column].x < grid->min_x)
		grid->min_x = grid->point_grid[row][column].x;
	if (grid->point_grid[row][column].y < grid->min_y)
		grid->min_y = grid->point_grid[row][column].y;
}

map_grid	*ft_fill_grid(char **argv, map_grid *grid)
{
	int		fd;
	char	*map_line;
	char	**map_array;
	int 	row;
	int 	column;

	map_line = NULL;
	map_array = NULL;
	row = 0;
	column = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (NULL);
		//error_free();
	grid->point_grid = (point **)malloc((grid->height + 1) * sizeof(point *));
	if (grid->point_grid == NULL)
		return (NULL);
		//error_free();
	while (row < grid->height)
	{
		map_line = get_next_line(fd);
		map_array = ft_split(map_line, ' ');
		if (grid->point_grid == NULL)
			return (NULL);
			//error_free();
		grid->point_grid[row] = (point *)malloc((grid->width + 1) * sizeof(point));
		while (column < grid->width)
		{
			ft_fill_points(map_array, &grid->point_grid[row][column] , row, column);
			ft_min_max(grid, row, column);
			// ft_draw_lines(grid, i, j);
			column++;
		}
		// grid->point_grid[row][column] = NULL;// ????????????????????????????????????????????????????
		row++;
		column = 0;
		free(map_line);
		free(map_array);
	}
	grid->point_grid[row] = NULL;
	close(fd);
	return (grid);
}

int	ft_strnum(char const *s, char c, int strnum)
{
	int	i;

	i = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	if (s[i] == '\0')
		return (0);
	if (c == '\0' && i > 0)
		return (1);
	strnum = 1;
	while (s[i] != '\0')
	{
		if (s[i] == c && i != 0 && s[i - 1] != c)
			strnum++;
		if (s[i] == c && s[i + 1] == '\0')
			strnum--;
		i++;
	}
	return (strnum);
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
	grid->width = ft_strnum(map_line, ' ', 0);
	while (1)
	{
		grid->height++;
		map_line = get_next_line(fd);
		if (map_line == NULL)
			break;
		// if (ft_strnum(map_line, ' ', 0) != grid->width)
			// ft_error();
	}
	close(fd);
	return (grid);
}

map_grid	*ft_make_grid(char **argv, map_grid *grid)
{
	grid = (map_grid *)malloc(sizeof(map_grid));
	if (grid == NULL)
		return(NULL);
	grid->max_x = FLT_MIN;
	grid->max_y = FLT_MIN;
	grid->min_x = FLT_MAX;	
	grid->min_y = FLT_MAX;	
	grid = ft_grid_size(argv, grid);
	grid = ft_fill_grid(argv, grid);

	// printf("grid->height = %d  |  grid->width = %d \n", grid->height, grid->width);

	return (grid);
}

int	ft_scale(map_grid *grid, float scale, int img_dim)
{
	int		row;
	int		column;
	float	offset;

	row = 0;
	column = 0;
	if (grid->max_x - grid->min_x > grid->max_y - grid->min_y)
		scale = (img_dim - 100) / (grid->max_x - grid->min_x);
	else
		scale = (img_dim - 100) / (grid->max_y - grid->min_y);
	// printf("scale = %f  |  x diff = %f  |   y diff = %f   \n", scale , grid->max_x - grid->min_x, grid->max_y - grid->min_y);
	while (row < grid->height)
	{
		while (column < grid->width)
		{
			offset = (img_dim - 100 - (scale * (grid->max_x - grid->min_x))) / 2;
			// printf("BEFORE x = %f  |  y = %f  |  colour = %x\n", grid->point_grid[row][column].x, grid->point_grid[row][column].y, grid->point_grid[row][column].colour);
			grid->point_grid[row][column].x = (scale * (grid->point_grid[row][column].x - grid->min_x)) + offset;
			offset = (img_dim - 100 - (scale * (grid->max_y - grid->min_y))) / 2;
			grid->point_grid[row][column].y = (scale * (grid->point_grid[row][column].y - grid->min_y)) + offset;
			// printf("AFTER x = %f  |  y = %f  |  colour = %x\n", grid->point_grid[row][column].x, grid->point_grid[row][column].y, grid->point_grid[row][column].colour);
			column++;
		}
		row++;
		column = 0;
	}
	return (scale);
}

void	ft_draw_line_back(map_grid *grid, int row, int column, mlx_image_t *img)
{
	int		dx;
	int		dy;
	int		f;
	int		x;
	int		y;
	
	dx = (int)grid->point_grid[row][column].x - (int)grid->point_grid[row][column - 1].x;
	dy = (int)grid->point_grid[row][column].y - (int)grid->point_grid[row][column - 1].y;
	x = (int)grid->point_grid[row][column - 1].x;
	y = (int)grid->point_grid[row][column - 1].y;
	
	// printf("\n\nBACK -> x-1 = %d  x = %d   |   y-1 = %d  y = %d \n", (int)grid->point_grid[row][column - 1].x, (int)grid->point_grid[row][column].x, (int)grid->point_grid[row][column - 1].y, (int)grid->point_grid[row][column].y);
	// printf("x = %d  dx = %d   |   y = %d  dy = %d  |  row = %d  column = %d\n", x, dx, y, dy, row, column);

	if (dy < 0 && dx > (-1 * dy))
	{
		f = dx / 2;
		while (x + 1 < (int)grid->point_grid[row][column].x)
		{
			x++;
			f = f + dy;
			if (f < 0)
			{
				f = f + dx;
				y--;
			}
			// printf("(a) x = %d  y = %d | ", x, y);
			mlx_put_pixel(img, x, y, 0xFFFFFFFF);
		}
	}
	else if (dy < 0 && dx < (-1 * dy))
	{
		f = -dy / 2;
		while (y - 1 > (int)grid->point_grid[row][column].y)
		{
			y--;
			f = f - dx;
			if (f < 0)
			{
				f = f - dy;
				x++;
			}
			// printf("(b) x = %d  y = %d | ", x, y);
			mlx_put_pixel(img, x, y, 0xFFFFFFFF);
		}
	}
	else if (dx > dy)
	{
		f = dx / 2;
		while (x + 1 < (int)grid->point_grid[row][column].x)
		{
			x++;
			f = f - dy;
			if (f < 0)
			{
				f = f + dx;
				y++;
			}
			// printf("(A) x = %d  y = %d | ", x, y);
			mlx_put_pixel(img, x, y, 0xFFFFFFFF);
		}
	}
	else
	{
		f = dy / 2;
		while (y + 1 < (int)grid->point_grid[row][column].y)
		{
			y++;
			f = f - dx;
			if (f < 0)
			{
				f = f + dy;
				x++;
			}
			// printf("(B) x = %d  y = %d | ", x, y);
			mlx_put_pixel(img, x, y, 0xFFFFFFFF);
		}
	}
}


//need to change to bitshifting!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
uint32_t ft_line_colour_up(map_grid *grid, int row, int column, int x)
{
	uint32_t	pixel_colour;
	uint32_t	dcolour;
	float		dx;
	float		colour_percent;

	if (grid->point_grid[row][column].colour == grid->point_grid[row - 1][column].colour)
		return(grid->point_grid[row][column].colour);
	dcolour = grid->point_grid[row][column].colour - grid->point_grid[row - 1][column].colour;
	dx = grid->point_grid[row][column].x - grid->point_grid[row - 1][column].x;
	if (dx < 0)
		dx *= -1;
	colour_percent = (x - grid->point_grid[row][column].x) / dx;
	printf("\n\n>>>>colour_percent = %f, dx = %f,  x = %d\n\n", colour_percent, dx, x);
	pixel_colour = (dcolour * colour_percent) + grid->point_grid[row][column].colour;
	printf("\n\n>>>>start col = %x, pix col = %x, end col = %x\n", grid->point_grid[row][column].colour, pixel_colour, grid->point_grid[row - 1][column].colour);
	printf(">>>>start col = %d, pix col = %d, end col = %d,  dcolour = %d\n\n", grid->point_grid[row][column].colour, pixel_colour, grid->point_grid[row - 1][column].colour, dcolour);
	return(pixel_colour);
}

void	ft_draw_line_up(map_grid *grid, int row, int column, mlx_image_t *img)
{
	int		dx;
	int		dy;
	int		f;
	int		x;
	int		y;
	
	dx = (int)grid->point_grid[row - 1][column].x - (int)grid->point_grid[row][column].x;
	dy = (int)grid->point_grid[row - 1][column].y - (int)grid->point_grid[row][column].y;
	x = (int)grid->point_grid[row][column].x;
	y = (int)grid->point_grid[row][column].y;
	
	// printf("\n\nUP -> x-1 = %d  x = %d   |   y-1 = %d  y = %d \n", (int)grid->point_grid[row - 1][column].x, (int)grid->point_grid[row][column].x, (int)grid->point_grid[row - 1][column].y, (int)grid->point_grid[row][column].y);
	// printf("x = %d  dx = %d   |   y = %d  dy = %d  |  row = %d  column = %d\n", x, dx, y, dy, row, column);

	if (dy < 0 && dx > (-1 * dy))
	{
		f = dx / 2;
		while (x + 1 < (int)grid->point_grid[row - 1][column].x)
		{
			x++;
			f = f + dy;
			if (f < 0)
			{
				f = f + dx;
				y--;
			}
			// printf("(a) x = %d  y = %d | ", x, y);
			mlx_put_pixel(img, x, y, ft_line_colour_up(grid, row, column, x));
		}
	}
	else if (dy < 0 && dx < (-1 * dy))
	{
		f = -dy / 2;
		while (y - 1 > (int)grid->point_grid[row - 1][column].y)
		{
			y--;
			f = f - dx;
			if (f < 0)
			{
				f = f - dy;
				x++;
			}
			// printf("(b) x = %d  y = %d | ", x, y);
			mlx_put_pixel(img, x, y, ft_line_colour_up(grid, row, column, x));
		}
	}
	else if (dx > dy)
	{
		f = dx / 2;
		while (x + 1 < (int)grid->point_grid[row - 1][column].x)
		{
			x++;
			f = f - dy;
			if (f < 0)
			{
				f = f + dx;
				y++;
			}
			// printf("(A) x = %d  y = %d | ", x, y);
			mlx_put_pixel(img, x, y, ft_line_colour_up(grid, row, column, x));
		}
	}
	else
	{
		f = dy / 2;
		while (y + 1 < (int)grid->point_grid[row - 1][column].y)
		{
			y++;
			f = f - dx;
			if (f < 0)
			{
				f = f + dy;
				x++;
			}
			// printf("(B) x = %d  y = %d | ", x, y);
			mlx_put_pixel(img, x, y, ft_line_colour_up(grid, row, column, x));
		}
	}
}


int32_t	main(int argc, char **argv)
{

	// ft_parse_map();

	int		row;
	int		column;

	float		scale;
	int32_t		img_dim;
	// point	*pix;
	map_grid	*grid;


	row = 0;
	column = 0;
	img_dim = 1300;
	scale = 1;
	grid = NULL;

	mlx_t*	mlx;

	if (argc != 2)
		exit(EXIT_FAILURE);

	mlx_set_setting(MLX_MAXIMIZED, false);
	mlx = mlx_init(img_dim, img_dim, "FDF - MAP", true);
	if (!mlx)
		ft_error();

	mlx_image_t* img = mlx_new_image(mlx, img_dim, img_dim);
	if (!img)
		ft_error();

	grid = ft_make_grid(argv, grid);
	if (grid == NULL)
		exit (EXIT_FAILURE);

	// printf("grid->max_x = %f  |  grid->max_y = %f  |  grid->min_x = %f  |  grid->min_y = %f \n", grid->max_x, grid->max_y, grid->min_x, grid->min_y);


	scale = ft_scale(grid, scale, img_dim);
	
	// printf("grid->height = %d  |  grid->width = %d  |  scale = %f\n", grid->height, grid->width, scale);

	
	while (row < grid->height)
	{
		while (column < grid->width)
		{
			// printf("x = %f  |  y = %f  |  colour = %x\n", grid->point_grid[row][column].x, grid->point_grid[row][column].y, grid->point_grid[row][column].colour);
			
			mlx_put_pixel(img, grid->point_grid[row][column].x, grid->point_grid[row][column].y, grid->point_grid[row][column].colour);
			if (column > 0)
				ft_draw_line_back(grid, row, column, img);
			if (row > 0)
				ft_draw_line_up(grid, row, column, img);
			
			column++;
		}
		row++;
		column = 0;
	}
	// fd = open(argv[1], O_RDONLY);
	// if (fd == -1)
	// 	return (1);
	// while (1)
	// {
	// 	map_line = get_next_line(fd);
	// 	if (map_line == NULL)
	// 		break;
	// 	map_array = ft_split(map_line, ' ');
	// 	while (map_array[x_coord] != NULL)
	// 	{
	// 		pix = ft_make_point(map_array, x_coord, y_coord, scale);
	// 		// pix = ft_trans_iso(pix);
	// 		printf("x = %f, y = %f\n", pix->x, pix->y);
	// 		mlx_put_pixel(img, pix->x, pix->y, pix->colour);
	// 		x_coord++;
	// 	}
	// 	y_coord++;
	// 	x_coord = 0;
	// }
	// close(fd);

	// mlx_put_pixel(img, 500, 400, 0xFFAFF1F2);

	if (mlx_image_to_window(mlx, img, 50, 50) < 0)
		ft_error();

	if (!mlx_put_string(mlx, "scale", 50, 50))
		ft_error();

	mlx_loop(mlx);

	// mlx_new_window();

	mlx_terminate(mlx);
	// ft_free_all();
	return (EXIT_SUCCESS);
}









// int32_t	main(int argc, char **argv)
// {

// 	// ft_parse_map();
// 	char	*map_line;
// 	char	**map_array;
// 	int		fd;
// 	int		x_coord;
// 	int		y_coord;
// 	int		scale;
// 	int32_t	height;
// 	int32_t	width;

// 	map_line = NULL;
// 	x_coord = 0;
// 	y_coord = 0;
// 	height = 800;
// 	width = 1200;
	
// 	mlx_t*	mlx;
	
// 	if (argc != 2)
// 		exit(EXIT_FAILURE);
	
// 	mlx_set_setting(MLX_MAXIMIZED, false);
// 	mlx = mlx_init(width, height, "FDF - MAP", true);
// 	if (!mlx)
// 		ft_error();

// 	mlx_image_t* img = mlx_new_image(mlx, width, height);
// 	if (!img)
// 		ft_error();

// 	fd = open(argv[1], O_RDONLY);
// 	if (fd == -1)
// 		return (1);
// 	while (1)
// 	{
// 		map_line = get_next_line(fd);
// 		if (map_line == NULL)
// 			break;
// 		map_array = ft_split(map_line, ' ');
// 		while (map_array[x_coord] != NULL)
// 		{
// 			if (ft_atoi(&map_array[x_coord][0]) == 10)
// 				mlx_put_pixel(pix, x_coord + (width/2), y_coord + (height/2), 0xFF0000FF);
// 			else
// 				mlx_put_pixel(pix, x_coord + (width/2), y_coord + (height/2), 0x0CFF00FF);
// 			x_coord++;
// 		}
// 		y_coord++;
// 		x_coord = 0;
// 	}	
// 	// mlx_put_pixel(img, 500, 400, 0xFFAFF1F2);

// 	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
// 		ft_error();

// 	if (!mlx_put_string(mlx, "fdf project map", 50, 50))
// 		ft_error();

// 	mlx_loop(mlx);

// 	// mlx_new_window();

// 	mlx_terminate(mlx);
// 	return (EXIT_SUCCESS);
// }




	// // Create and display the image.
	// mlx_image_t* img = mlx_new_image(mlx, 256, 256);
	// if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
	// 	ft_error();

	// // Even after the image is being displayed, we can still modify the buffer.
	// mlx_put_pixel(img, 0, 0, 0xFF0000FF);

	// // Register a hook and pass mlx as an optional param.
	// // NOTE: Do this before calling mlx_loop!
	// mlx_loop_hook(mlx, ft_hook, mlx);
	// mlx_loop(mlx);
	// mlx_terminate(mlx);
	// return (EXIT_SUCCESS);
	