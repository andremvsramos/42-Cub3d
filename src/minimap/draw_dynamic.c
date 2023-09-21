/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_dynamic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:32:51 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/09/21 15:44:46 by tsodre-p         ###   ########.fr       */
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

void	draw_dynamic_map(t_Cub3d *cub)
{
	int	x;
	int	y;

	y = (int)cub->player->pos_y - 5;
	while (y < (y + 11))
	{
		x = (int)cub->player->pos_x - 5;
		if (y < 0)
		{
			y++;
			cub->minimap->draw_y += 13;
		}
		else
		{
			if (x < 0)
			{
				cub->minimap->draw_x += 13;
				x++;
			}
			else
			{
				while (x < (x + 11))
				{
					if (ft_strchr("1", cub->map->matrix[y][x]))
						draw_dynamic_cube(cub, GREY);
					else if (ft_strchr("0", cub->map->matrix[y][x]))
						draw_dynamic_cube(cub, WHITE);
					x++;
					cub->minimap->draw_x += 13;
				}
				cub->minimap->draw_y += 13;
				cub->minimap->draw_x = 0;
				y++;
			}
		}
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
