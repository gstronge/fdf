/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_colours.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:38:08 by gstronge          #+#    #+#             */
/*   Updated: 2024/06/12 18:49:14 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

char	*ft_make_rgb(t_map *grid, char *str, char *rgb, char *other_rgb)
{
	if (!rgb)
	{
		rgb = (char *)malloc(3 * sizeof(char));
		if (rgb == NULL)
		{
			if (other_rgb)
				free(other_rgb);
			ft_error("malloc error", errno, grid);
		}
	}
	rgb[0] = '\0';
	rgb[1] = '\0';
	rgb[2] = '\0';
	if (str[0])
		rgb[0] = str[0];
	if (str[1])
		rgb[1] = str[1];
	return (rgb);
}

uint32_t	ft_rgb_int(char *str)
{
	uint32_t	colour;
	int			i;

	colour = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] <= '9' && str[i] >= '0')
			colour = (colour * 16) + str[i] - '0';
		else if (str[i] <= 'F' && str[i] >= 'A')
			colour = (colour * 16) + str[i] - 'A' + 10;
		else if (str[i] <= 'f' && str[i] >= 'a')
			colour = (colour * 16) + str[i] - 'a' + 10;
		i++;
	}
	return (colour);
}

uint32_t	ft_av_colour(t_map *grid, char *clr_a, char *clr_b, uint32_t avrg)
{
	char	*rgb_a;
	char	*rgb_b;
	int		i;

	i = 0;
	rgb_a = NULL;
	rgb_b = NULL;
	while (i < 6 && (clr_a[i] != '\0' && clr_b[i] != '\0'))
	{
		rgb_a = ft_make_rgb(grid, &clr_a[i], rgb_a, rgb_b);
		rgb_b = ft_make_rgb(grid, &clr_b[i], rgb_b, rgb_a);
		avrg = avrg << 8 | (ft_rgb_int(rgb_a) + ft_rgb_int(rgb_b)) / 2;
		i += 2;
	}
	avrg = avrg << 8;
	avrg += 255;
	free(rgb_a);
	free(rgb_b);
	return (avrg);
}

uint32_t	ft_line_colour(t_map *grid, int row, int col, t_line_pix line)
{
	uint32_t	colour;

	colour = 0;
	if (line.r_or_c == 'r')
	{
		if (!ft_strncmp(grid->points[row][col].colour_pix, \
				grid->points[row - 1][col].colour_pix, 8))
			colour = ft_hex_to_int(grid->points[row][col].colour_pix);
		else
			colour = ft_av_colour(grid, grid->points[row][col].colour_pix,
					grid->points[row - 1][col].colour_pix, colour);
	}
	else if (line.r_or_c == 'c')
	{
		if (!ft_strncmp(grid->points[row][col].colour_pix, \
				grid->points[row][col - 1].colour_pix, 8))
			colour = ft_hex_to_int(grid->points[row][col].colour_pix);
		else
			colour = ft_av_colour(grid, grid->points[row][col].colour_pix,
					grid->points[row][col - 1].colour_pix, colour);
	}
	return (colour);
}
