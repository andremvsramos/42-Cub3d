/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:50:37 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/09/20 17:03:48 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

static int	check_minimap_size_height(t_Cub3d *cub, int max_height)
{
	if (((cub->map->n_lines + 1) * 13) <= max_height)
		return (((cub->map->n_lines + 1) * 13));
	else
		return (cub->minimap->flag = 1, max_height);
}

static int	check_minimap_size_width(t_Cub3d *cub, int max_width)
{
	if (((cub->map->max_line_len - 1) * 13) <= max_width)
		return ((cub->map->max_line_len - 1) * 13);
	else
		return (cub->minimap->flag = 1, max_width);
}

void	init_minimap(t_Cub3d *cub)
{
	cub->minimap = ft_calloc(1, sizeof(t_MiniMap));
	cub->minimap->img = ft_calloc(1, sizeof(t_ImageControl));
	/* cub->minimap->width = 10 * (cub->map->max_line_len - 1);
	cub->minimap->height = 10 * (cub->map->n_lines + 1); */
	cub->minimap->width = check_minimap_size_width(cub, 143);
	cub->minimap->height = check_minimap_size_height(cub, 143);
}

int	draw_minimap(t_Cub3d *cub)
{
	cub->minimap->player_x = ((int)cub->player->pos_x) * 13;
	cub->minimap->player_y = ((int)cub->player->pos_y) * 13;
	if (cub->minimap->flag == 0)
	{
		draw_static_map(cub);
		draw_static_player(cub);
	}
	else
	{
		draw_dynamic_map(cub, 0, 0);
		draw_dynamic_player(cub);
	}
	return (0);
}
