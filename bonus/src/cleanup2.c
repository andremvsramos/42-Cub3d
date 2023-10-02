/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:07:17 by andvieir          #+#    #+#             */
/*   Updated: 2023/10/02 10:01:24 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d_bonus.h"

/**
 * @brief Deallocate resources associated with the in-game menu in Cub3D.
 *
 * The `free_menu` function is responsible for freeing memory and resources
 * associated with the in-game menu in the Cub3D game. It checks if the menu
 * is active (`menu_ok` flag) and proceeds to free any textures used by the
 * menu, such as start and quit buttons. Finally, it frees the memory allocated
 * for the menu structure and sets the `menu_active` flag to false, indicating
 * that the menu is no longer in use.
 *
 * @param cub Pointer to the Cub3D game configuration structure.
 */
void	free_menu(t_Cub3d *cub)
{
	if (cub->menu_ok)
	{
		if (cub->main->start)
			free_textures(cub, cub->main->start);
		if (cub->main->quit)
			free_textures(cub, cub->main->quit);
		free(cub->main);
	}
	cub->menu_active = false;
}

/**
 * @brief Deallocate resources associated with the player's gun and crosshair.
 *
 * The `free_gun` function is responsible for freeing memory and resources
 * associated with the player's gun and crosshair in the Cub3D game. It checks
 * if these resources are initialized (`gun_ok` flag) and proceeds to free
 * any textures used for the gun and crosshair. This ensures that memory is
 * properly released when these elements are no longer needed.
 *
 * @param cub Pointer to the Cub3D game configuration structure.
 */
void	free_gun(t_Cub3d *cub)
{
	if (cub->gun_ok)
	{
		if (cub->player->gun)
			free_textures(cub, cub->player->gun);
		if (cub->player->crosshair)
			free_textures(cub, cub->player->crosshair);
	}
}

/**
 * @brief Deallocate resources associated with camera textures and
 * configurations.
 *
 * The `free_cam` function is responsible for freeing memory and resources
 * associated with camera textures and configurations in the Cub3D game. It
 * releases memory allocated for various textures, including north, south,
 * west, and east textures, as well as door textures in case of the bonus.
 * If file-related resources are initialized (`files_ok` flag), it frees the
 * memory used for the textures stored in the camera structure. Finally, the
 * function frees the memory allocated for the camera texture array and other
 * related data.
 *
 * @param cub Pointer to the Cub3D game configuration structure.
 */
void	free_cam(t_Cub3d *cub)
{
	int	i;

	i = 0;
	if (cub->map->tex_north)
		free_textures(cub, cub->map->tex_north);
	if (cub->map->tex_south)
		free_textures(cub, cub->map->tex_south);
	if (cub->map->tex_west)
		free_textures(cub, cub->map->tex_west);
	if (cub->map->tex_east)
		free_textures(cub, cub->map->tex_east);
	if (BONUS && cub->map->tex_door)
		free_textures(cub, cub->map->tex_door);
	if (cub->files_ok)
	{
		while (i < 4 + BONUS)
		{
			if (cub->cam->tex[i])
				free(cub->cam->tex[i]);
			i++;
		}
		free(cub->cam->tex);
	}
}
