/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:50:37 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/09/28 10:09:08 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d_bonus.h"

/**
 * @brief Create a new image for the minimap and configure its properties.
 *
 * The `minimap_new_image` function destroys the existing minimap image, creates
 * a new image with the specified dimensions (width and height), and configures
 * its address and properties. It also resets the drawing position for the
 * minimap.
 *
 * This function is used to update the minimap image when the size or content
 * needs to change.
 *
 * @param cub Pointer to the Cub3D game configuration structure.
 */
void	minimap_new_image(t_Cub3d *cub)
{
	mlx_destroy_image(cub->mlx_ptr, cub->minimap->img->img_ptr);
	cub->minimap->img->img_ptr = mlx_new_image(cub->mlx_ptr,
			cub->minimap->width, cub->minimap->height);
	cub->minimap->img->addr = mlx_get_data_addr(
			cub->minimap->img->img_ptr, &cub->minimap->img->bpp,
			&cub->minimap->img->len, &cub->minimap->img->endian);
	cub->minimap->draw_x = 0;
	cub->minimap->draw_y = 0;
}

/**
 * @brief Check and determine the minimap's height based on the maximum allowed
 * height.
 *
 * The `check_minimap_size_height` function calculates the minimap's height based
 * on the maximum allowed height (max_height) while ensuring it fits within the
 * specified constraints. If the minimap size exceeds the constraints, it sets
 * a flag indicating that the minimap needs to be adjusted.
 *
 * @param cub Pointer to the Cub3D game configuration structure.
 * @param max_height The maximum allowed height for the minimap.
 * @return The calculated minimap height, considering constraints.
 */
static int	check_minimap_size_height(t_Cub3d *cub, int max_height)
{
	if (((cub->map->n_lines + 1) * 13) <= max_height)
		return (((cub->map->n_lines + 1) * 13));
	else
		return (cub->minimap->flag = 1, max_height);
}

/**
 * @brief Check and determine the minimap's width based on the maximum allowed
 * width.
 *
 * The `check_minimap_size_width` function calculates the minimap's width based
 * on the maximum allowed width (max_width) while ensuring it fits within the
 * specified constraints. If the minimap size exceeds the constraints, it sets
 * a flag indicating that the minimap needs to be adjusted.
 *
 * @param cub Pointer to the Cub3D game configuration structure.
 * @param max_width The maximum allowed width for the minimap.
 * @return The calculated minimap width, considering constraints.
 */
static int	check_minimap_size_width(t_Cub3d *cub, int max_width)
{
	if ((max_x_array(cub) * 13) <= max_width)
		return ((max_x_array(cub) * 13));
	else
		return (cub->minimap->flag = 1, max_width);
}

/**
 * @brief Initialize the minimap, including its dimensions and image properties.
 *
 * The `init_minimap` function initializes the minimap by allocating memory for
 * the minimap and image control structures. It determines the minimap's width
 * and height based on constraints and sets the image address and properties.
 * If adjustments are needed due to constraints, it sets a flag accordingly.
 *
 * @param cub Pointer to the Cub3D game configuration structure.
 */
void	init_minimap(t_Cub3d *cub)
{
	cub->minimap = ft_calloc(1, sizeof(t_MiniMap));
	cub->minimap->img = ft_calloc(1, sizeof(t_ImageControl));
	cub->minimap->width = check_minimap_size_width(cub, 143);
	cub->minimap->height = check_minimap_size_height(cub, 143);
	if (cub->minimap->flag == 1)
	{
		cub->minimap->width = 143;
		cub->minimap->height = 143;
	}
	cub->minimap->img->img_ptr = mlx_new_image(cub->mlx_ptr,
			cub->minimap->width, cub->minimap->height);
	cub->minimap->img->addr = mlx_get_data_addr(
			cub->minimap->img->img_ptr, &cub->minimap->img->bpp,
			&cub->minimap->img->len, &cub->minimap->img->endian);
	cub->minimap->draw_x = 0;
	cub->minimap->draw_y = 0;
	cub->minimap_ok = true;
}

/**
 * @brief Draw the minimap on the game screen.
 *
 * The `draw_minimap` function is responsible for rendering the minimap on the
 * game screen. It calculates the player's position on the minimap and draws
 * either the static map or the dynamic map based on the flag. This function
 * plays a crucial role in providing the player with a visual representation of
 * the game world.
 *
 * @param cub Pointer to the Cub3D game configuration structure.
 * @return An integer value indicating the success (0) of the minimap drawing.
 */
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
