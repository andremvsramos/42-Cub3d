/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_dynamic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: programming-pc <programming-pc@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:32:51 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/09/27 21:47:06 by programming      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void	draw_dynamic_cube(t_Cub3d *cub, int type)
{
	int	i;
	int	j;

	i = 0;
	j = 0;

	while (i < 13)
	{
		j = 0;
		while (j < 13)
		{
			my_mlx_pixel_put(cub->minimap->img, (cub->minimap->draw_x + j),
					(cub->minimap->draw_y + i), type);
			j++;
		}
		i++;
	}
}

void	draw_dynamic_map(t_Cub3d *cub, int temp_x, int temp_y)
{
	int	x;
	int	y;

	y = (int)cub->player->pos_y - 5;
	temp_y = y;
	while (y < (temp_y + 11))
	{
		x = (int)cub->player->pos_x - 5;
		temp_x = x;
		while (x < (temp_x + 11))
		{
			if (y >= cub->map->n_lines + 1 || y < 0 ||
				x >= max_x_array(cub) || x < 0)
				draw_dynamic_cube(cub, BLACK);
			else if (ft_strchr("19 ", cub->map->matrix[y][x]))
				draw_dynamic_cube(cub, GREY);
			else if (ft_strchr("0NSWE", cub->map->matrix[y][x]))
				draw_dynamic_cube(cub, WHITE);
			x++;
			cub->minimap->draw_x += 13;
		}
		cub->minimap->draw_y += 13;
		cub->minimap->draw_x = 0;
		y++;
	}
}

void	draw_dynamic_player(t_Cub3d *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 13)
	{
		j = 0;
		while (j < 13)
		{
			my_mlx_pixel_put(cub->minimap->img, ((13 * 5) + j),
				((13 * 5)  + i), RED);
			j++;
		}
		i++;
	}
}
