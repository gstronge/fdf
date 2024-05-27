/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:04:10 by gstronge          #+#    #+#             */
/*   Updated: 2024/05/27 19:12:06 by gstronge         ###   ########.fr       */
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
ft_calculate_(and maybe draw)lines > Bresenham
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

point	*ft_isometric(point *pixel)
{
	float	temp_x;
	float	temp_y;
	
	temp_x = pixel->x;
	temp_y = pixel->y;
	pixel->x = (sqrt(2)/2) * (temp_x - temp_y);//need to remove the sqrt function!!!!!!!!!!!
	pixel->y = ((sqrt(6)/6) * (temp_x + temp_y)) - ((sqrt(3)/3) * pixel->z);//need to remove the sqrt function!
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

point	*ft_make_point(char **map_array, int x_coord, int y_coord, int scale)
{
	point	*pixel;
	int		i;

	i = 0;
	pixel = (point *)malloc(sizeof(point));
	while (map_array[x_coord][i] != ',' && map_array[x_coord][i] != '\0')
		i++;
	if (map_array[x_coord][i] == '\0')
		pixel->colour = 0xFFFFFFFF;
	else
		pixel->colour = ft_colour(&map_array[x_coord][i + 3]);
	// printf(" z = %f colour after = %x\n",pixel->z, pixel->colour);//=============================================
	pixel->x = (x_coord * scale) + 500;
	pixel->y = (y_coord * scale) + 200;
	pixel->z = ft_atoi(map_array[x_coord]) * scale;
	pixel = ft_isometric(pixel);
	// printf(" z = %f colour before = %x ",pixel->z, pixel->colour);//=============================================
	return(pixel);
}


int32_t	main(int argc, char **argv)
{

	// ft_parse_map();
	char	*map_line;
	char	**map_array;
	int		fd;
	int		x_coord;
	int		y_coord;
	int		scale;
	int32_t	height;
	int32_t	width;
	point	*pix;

	map_line = NULL;
	x_coord = 0;
	y_coord = 0;
	height = 1200;
	width = 1800;
	scale = 50;
	
	mlx_t*	mlx;
	
	if (argc != 2)
		exit(EXIT_FAILURE);
	
	mlx_set_setting(MLX_MAXIMIZED, false);
	mlx = mlx_init(width, height, "FDF - MAP", true);
	if (!mlx)
		ft_error();

	mlx_image_t* img = mlx_new_image(mlx, width, height);
	if (!img)
		ft_error();

	// grid = ft_make_grid();
	
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (1);
	while (1)
	{
		map_line = get_next_line(fd);
		if (map_line == NULL)
			break;
		map_array = ft_split(map_line, ' ');
		while (map_array[x_coord] != NULL)
		{
			pix = ft_make_point(map_array, x_coord, y_coord, scale);
			// pix = ft_trans_iso(pix);
			printf("x = %f, y = %f\n", pix->x, pix->y);
			mlx_put_pixel(img, pix->x, pix->y, pix->colour);
			x_coord++;
		}
		y_coord++;
		x_coord = 0;
	}
	close(fd);
	// mlx_put_pixel(img, 500, 400, 0xFFAFF1F2);

	if (mlx_image_to_window(mlx, img, width/scale, height/scale) < 0)
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
	