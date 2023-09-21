/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:50:37 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/09/21 15:18:45 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

static int	check_minimap_size_height(t_Cub3d *cub, int max_height)
{
	if (((cub->map->n_lines + 1) * 13) < max_height)
		return (((cub->map->n_lines + 1) * 13));
	else
		return (max_height);
}

static int	check_minimap_size_width(t_Cub3d *cub, int max_width)
{
	if (((cub->map->max_line_len - 1) * 13) < max_width)
		return ((cub->map->max_line_len - 1) * 13);
	else
		return (max_width);
}

void	init_minimap(t_Cub3d *cub)
{
	cub->minimap = ft_calloc(1, sizeof(t_MiniMap));
	cub->minimap->img = ft_calloc(1, sizeof(t_ImageControl));
	/* cub->minimap->width = 10 * (cub->map->max_line_len - 1);
	cub->minimap->height = 10 * (cub->map->n_lines + 1); */
	cub->minimap->width = check_minimap_size_width(cub, 143);
	cub->minimap->height = check_minimap_size_height(cub, 143);
	cub->minimap->img->img_ptr = mlx_new_image(cub->mlx_ptr,
						cub->minimap->width, cub->minimap->height);
	cub->minimap->img->addr = mlx_get_data_addr(
			cub->minimap->img->img_ptr, &cub->minimap->img->bpp,
			&cub->minimap->img->len, &cub->minimap->img->endian);
	cub->minimap->draw_x = 0;
	cub->minimap->draw_y = 0;
}

int	draw_minimap(t_Cub3d *cub)
{
	cub->minimap->player_x = ((int)cub->player->pos_x) * 13;
	cub->minimap->player_y = ((int)cub->player->pos_y) * 13;
	if (cub->minimap->width < 143 || cub->minimap->height < 143)
	{
		draw_static_map(cub);
		draw_static_player(cub);
	}
	else
	{
		draw_dynamic_map(cub);
		draw_dynamic_player(cub);
	}
	return (0);
}
