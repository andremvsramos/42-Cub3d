/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: programming-pc <programming-pc@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:50:37 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/09/19 12:02:59 by programming      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void	init_minimap(t_Cub3d *cub)
{
	int	bpp;
	int	len;
	int	endian;

	cub->minimap = ft_calloc(1, sizeof(t_MiniMap));
	cub->minimap->img = ft_calloc(1, sizeof(t_ImageControl));
	cub->minimap->map_size = 12;
	cub->minimap->width = 10 * cub->map->max_line_len;
	cub->minimap->height = 10 * cub->map->n_lines;
	cub->minimap->img->img_ptr = mlx_new_image(cub->mlx_ptr,
						cub->minimap->width, cub->minimap->height);
	cub->minimap->img->addr = mlx_get_data_addr(
			cub->minimap->img->img_ptr, &bpp, &len, &endian);
	/* cub->minimap->draw_x = 30;
	cub->minimap->draw_y = 30; */
	cub->minimap->draw_x = 0;
	cub->minimap->draw_y = 0;
}

int	draw_minimap(t_Cub3d *cub)
{
	cub->minimap->player_x = cub->player->pos_x * 10;
	cub->minimap->player_y = cub->player->pos_y * 10;
	draw_map(cub);
	draw_player(cub);
	return (0);
}
