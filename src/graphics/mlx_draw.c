/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 22:21:18 by marvin            #+#    #+#             */
/*   Updated: 2023/08/29 22:21:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

static void	get_images(t_Cub3d *cub)
{
	int		img_width;
	int		img_height;
	int		*width;
	int		*height;

	img_width = 8;
	img_height = 8;
	width = &img_width;
	height = &img_height;
	cub->img_wall = mlx_xpm_file_to_image(
			cub->mlx_ptr, WALL_IMG, width, height);
	cub->img_floor = mlx_xpm_file_to_image(
			cub->mlx_ptr, FLOOR_IMG, width, height);
}

static void	image_conditions(t_Cub3d *cub, char miscellaneous, int x, int y)
{
	if (miscellaneous == '1')
		mlx_put_image_to_window(
			cub->mlx_ptr, cub->win_ptr, cub->img_wall, x, y);
	else
		mlx_put_image_to_window(
			cub->mlx_ptr, cub->win_ptr, cub->img_floor, x, y);
}

void	draw_2d_map(t_Cub3d *cub)
{
	get_images(cub);
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < cub->map->n_lines + 1)
	{
		j = 0;
		while (j < cub->map->max_line_len - 1)
		{
			if (cub->map->matrix[i][j] == '1')
				image_conditions(cub, '1', j * 8, i * 8);
			else
				image_conditions(cub, '0', j * 8, i * 8);
			j++;
		}
		i++;
	}
}


