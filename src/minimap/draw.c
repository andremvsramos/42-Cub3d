/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: programming-pc <programming-pc@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:50:43 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/09/20 11:56:58 by programming      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void	draw_cube(t_Cub3d *cub, int type)
{
	int	i;
	int	j;

	i = 0;
	j = 0;

	cub->minimap->width = 10 * cub->map->max_line_len;
	cub->minimap->height = 10 * (cub->map->n_lines + 1);
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			my_mlx_pixel_put(cub->minimap->img, (cub->minimap->draw_x + j),
					(cub->minimap->draw_y + i), type);
			j++;
		}
		i++;
	}
}

void	draw_map(t_Cub3d *cub)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < cub->map->n_lines + 1)
	{
		x = 0;
		while (x < cub->map->max_line_len - 3)
		{
			if (ft_strchr("1", cub->map->matrix[y][x]))
				draw_cube(cub, GREY);
			else if (ft_strchr("0NSEW", cub->map->matrix[y][x]))
				draw_cube(cub, WHITE);
			x++;
			cub->minimap->draw_x += 10;
		}
		cub->minimap->draw_y += 10;
		cub->minimap->draw_x = 0;
		y++;
	}
}

void	draw_player(t_Cub3d *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			my_mlx_pixel_put(cub->minimap->img, (((cub->player->pos_x * 10)) + j),
				((cub->player->pos_y * 10) + i), YELLOW);
			j++;
		}
		i++;
	}
}
