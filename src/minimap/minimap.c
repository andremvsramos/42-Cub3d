/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:50:37 by tsodre-p          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/09/20 17:03:48 by andvieir         ###   ########.fr       */
=======
/*   Updated: 2023/09/20 15:46:47 by programming      ###   ########.fr       */
>>>>>>> 0d8289b4bf08032a7f80a85ce1d3aa954950e0b3
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void	init_minimap(t_Cub3d *cub)
{
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
	cub->minimap->player_x = ((int)cub->player->pos_x) * 10;
	cub->minimap->player_y = ((int)cub->player->pos_y) * 10;
	//get_player_pos_matrix(cub);
	draw_map(cub);
	draw_player(cub);
	return (0);
}
