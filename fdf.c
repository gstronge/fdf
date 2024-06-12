/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:04:10 by gstronge          #+#    #+#             */
/*   Updated: 2024/06/12 19:22:39 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

void	keypress(mlx_key_data_t keydata, void *param)
{
	t_map	*grid;

	grid = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(grid->mlx);
}

int32_t	main(int argc, char **argv)
{
	t_map	*grid;
	int32_t	window_size;

	grid = NULL;
	window_size = 1200;
	ft_error_checks(argc, argv);
	grid = ft_make_grid(argv, grid, window_size);
	mlx_set_setting(MLX_MAXIMIZED, false);
	grid->mlx = mlx_init(window_size, window_size, "FDF - MAP", false);
	if (!grid->mlx)
		ft_error("error initialising mlx", errno, grid);
	ft_draw_image(grid, grid->window_size);
	if (mlx_image_to_window(grid->mlx, grid->img, 50, 50) < 0)
		ft_error("error adding image to window", errno, grid);
	mlx_key_hook(grid->mlx, keypress, grid);
	mlx_loop(grid->mlx);
	mlx_terminate(grid->mlx);
	ft_free_all(grid);
	return (EXIT_SUCCESS);
}
