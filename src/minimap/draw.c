/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:50:43 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/09/19 09:50:48 by tsodre-p         ###   ########.fr       */
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
	cub->minimap->height = 10 * cub->map->n_lines;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			/* mlx_pixel_put(cub->mlx_ptr, cub->win_ptr,
					(cub->minimap->draw_x + j), (cub->minimap->draw_y + i), type); */
			my_mlx_pixel_put(cub->minimap->img,(cub->minimap->draw_x + j),
					(cub->minimap->draw_y + i), type);
			//my_mlx_pixel_put(cub->minimap->img, 10, 10, WHITE);
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
			if (cub->map->matrix[y][x] == '1')
				draw_cube(cub, BLACK);
			else if (ft_strchr("0NSEW", cub->map->matrix[y][x]))
				draw_cube(cub, WHITE);
			cub->minimap->draw_x += 10;
			x++;
		}
		cub->minimap->draw_x = 0;
		cub->minimap->draw_y += 10;
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
			/* mlx_pixel_put(cub->mlx_ptr, cub->win_ptr,
					(((cub->player->pos_x * 10) + 30) + j), (((cub->player->pos_y * 10) + 30) + i), YELLOW); */
			my_mlx_pixel_put(cub->minimap->img, (((cub->player->pos_x * 10) + 30) + j),
				((cub->player->pos_y * 10) + i), YELLOW);
			j++;
		}
		i++;
	}
}
