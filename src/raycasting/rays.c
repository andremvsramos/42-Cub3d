/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: programming-pc <programming-pc@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:45:15 by andvieir          #+#    #+#             */
/*   Updated: 2023/09/06 10:37:04 by programming      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

/**
 * Raycasting per column.
 *
 * This function calculates ray direction and camera position for a given column
 * of the screen.
 *
 * @param cub A pointer to the Cub3d structure.
 * @param cam A pointer to the CameraConfig structure.
 * @param x The column index for which to calculate ray parameters.
 */
void	ray_per_colum(t_Cub3d *cub, t_CameraConfig *cam, int x)
{
	cam->camera_x = 2 * x / (double)WINDOW_X - 1;
	cam->raydir_x = cub->player->dir_x + cam->plane_x * cam->camera_x;
	cam->raydir_y = cub->player->dir_y + cam->plane_y * cam->camera_x;
}

/**
 * Update the camera's map position based on the player's position.
 *
 * This function calculates the map coordinates (grid position) of the player
 * based on their position in the game world.
 *
 * @param cub A pointer to the Cub3d structure.
 * @param cam A pointer to the CameraConfig structure.
 */
void	ray_map_pos(t_Cub3d *cub, t_CameraConfig *cam)
{
	cam->map_x = (int)cub->player->pos_x;
	cam->map_y = (int)cub->player->pos_y;
}

/**
 * Calculate the delta distances for ray steps in the X and Y directions.
 *
 * This function calculates the delta distances (step size) for raycasting in
 * both the X and Y directions based on the ray direction vectors in the camera
 * configuration.
 *
 * @param cam A pointer to the CameraConfig structure.
 */
void	ray_delt_dist(t_CameraConfig *cam)
{
	if (!cam->raydir_x)
		cam->ddist_x = 1e30;
	else
		cam->ddist_x = fabs(1 / cam->raydir_x);
	if (!cam->raydir_y)
		cam->ddist_y = 1e30;
	else
		cam->ddist_y = fabs(1 / cam->raydir_y);
}
