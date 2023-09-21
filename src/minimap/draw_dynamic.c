/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_dynamic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:32:51 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/09/21 14:32:53 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void	draw_cube(t_Cub3d *cub, int type)
{
	int	i;
	int	j;

	i = 0;
	j = 0;

	while (i < 15)
	{
		j = 0;
		while (j < 15)
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
		while (x < cub->map->max_line_len - 1)
		{
			if (ft_strchr("1", cub->map->matrix[y][x]))
				draw_cube(cub, GREY);
			else if (ft_strchr("0NSEW", cub->map->matrix[y][x]))
				draw_cube(cub, WHITE);
			x++;
			cub->minimap->draw_x += 15;
		}
		cub->minimap->draw_y += 15;
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
	while (i < 15)
	{
		j = 0;
		while (j < 15)
		{
			my_mlx_pixel_put(cub->minimap->img, (cub->minimap->player_x + j),
				(cub->minimap->player_y + i), RED);
			j++;
		}
		i++;
	}
}
