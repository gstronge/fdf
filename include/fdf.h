/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:06:20 by gstronge          #+#    #+#             */
/*   Updated: 2024/06/12 20:17:56 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <limits.h>
# include <errno.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"

typedef struct s_pixel
{
	float		x;
	float		y;
	float		z;
	char		*colour_pix;
}				t_pixel;

typedef struct s_line_pixel
{
	int			x;
	int			y;
	int			dx;
	int			dy;
	float		f;
	uint32_t	colour;
	char		r_or_c;
}				t_line_pix;

typedef struct s_map
{
	t_pixel			**points;
	int				width;
	int				height;
	float			scale;
	float			max_x;
	float			min_x;
	float			max_y;
	float			min_y;
	mlx_t			*mlx;
	mlx_image_t		*img;
	int32_t			window_size;
}					t_map;

//fdf - main function and function to close the window
void		keypress(mlx_key_data_t keydata, void *param);

//make_grid - functions to make the map/grid of points
t_map		*ft_make_grid(char **argv, t_map *grid, int32_t window_dims);
void		ft_grid_size(char **argv, t_map *grid, char *map_row);
int			ft_width_count(char const *s);
void		ft_fill_grid(char **argv, t_map *grid, char *map_row, char **split);
void		ft_scale(t_map *grid, int32_t dims);

//make_points - functions to make and fill the points on the grid/map
void		ft_parse_points(t_map *grid, int fd, char **split, int row);
void		ft_fill_points(char **map_array, t_map *grid, int row, int col);
void		ft_hex_to_str(t_map *grid, int row, int col, char *str);
void		ft_isometric(t_pixel *pix, int row, int col);
void		ft_min_max(t_map *grid, int row, int col);

//line_calcs - functions to calculate the lines between points
t_line_pix	ft_make_line(t_map *grid, int row, int col, char row_or_col);
void		ft_up_xg(t_line_pix line, int end, mlx_image_t *img);
void		ft_up_yg(t_line_pix line, int end, mlx_image_t *img);
void		ft_down_xg(t_line_pix line, int end, mlx_image_t *img);
void		ft_down_yg(t_line_pix line, int end, mlx_image_t *img);

//set_colours - functions for setting the colours for pixels and lines
char		*ft_make_rgb(t_map *grid, char *str, char *rgb, char *other_rgb);
uint32_t	ft_rgb_int(char *str);
uint32_t	ft_av_colour(t_map *grid, char *clr_a, char *clr_b, uint32_t avrg);
uint32_t	ft_line_colour(t_map *grid, int row, int col, t_line_pix line);

//make_image - functions to create the image for the window
void		ft_draw_line_col(t_map *grid, int row, int col, mlx_image_t *img);
void		ft_draw_line_row(t_map *grid, int row, int col, mlx_image_t *img);
uint32_t	ft_hex_to_int(char *str);
void		ft_draw_pix_on_img(t_map *grid, t_pixel *pix, int32_t window_size);
void		ft_draw_image(t_map *grid, int32_t window_size);

//error_cleanup - functions for handling errors and freeing
void		ft_error(char *message, int error_no, t_map *grid);
void		ft_error_checks(int argc, char **argv);
void		ft_free_all(t_map *grid);
void		ft_free_split(char **map_array);

#endif