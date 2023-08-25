/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 21:48:20 by marvin            #+#    #+#             */
/*   Updated: 2023/08/25 21:48:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

/**
 * @brief Calculate the step along the y-axis and side distance for raycasting.
 *
 * This function calculates the step along the y-axis (step_y) and the side
 * distance (side_dist_y) based on the ray's vertical direction. If the ray's
 * direction is negative along the y-axis, step_y is set to -1, and the
 * side_dist_y is calculated as the product of the difference between the
 * player's y-position and the map's y-coordinate, and the delta distance along
 * the y-axis. If the ray's direction is positive along the y-axis, step_y is
 * set to 1, and the side_dist_y is calculated using the difference between
 * the map's y-coordinate and the player's y-position, plus 1.0, and the delta
 * distance along the y-axis.
 *
 * @note If the game doesn't require complex vertical movement, this function
 * can be excluded from the raycasting process, as vertical raycasting won't be
 * utilized.
 *
 * @param cub Pointer to the t_Cub3d structure containing program context
 * and data.
 */
static void	get_step_y(t_Cub3d *cub)
{
	if (cub->cam->raydir_y < 0)
	{
		cub->cam->step_y = -1;
		cub->cam->side_dist_y =
			(cub->player->pos_y - cub->cam->map_y) * cub->cam->delta_dist_y;
	}
	else
	{
		cub->cam->step_y = 1;
		cub->cam->side_dist_y =
			(cub->cam->map_y + 1.0 - cub->player->pos_y) *
			cub->cam->delta_dist_y;
	}
}

/**
 * @brief Calculate the step along the x-axis and side distance for raycasting.
 *
 * This function calculates the step along the x-axis (step_x) and the side
 * distance (side_dist_x) based on the ray's horizontal direction. If the ray's
 * direction is negative along the x-axis, step_x is set to -1, and the
 * side_dist_x is calculated as the product of the difference between the
 * player's x-position and the map's x-coordinate, and the delta distance along
 * the x-axis. If the ray's direction is positive along the x-axis, step_x is
 * set to 1, and the side_dist_x is calculated using the difference between
 * the map's x-coordinate and the player's x-position, plus 1.0, and the delta
 * distance along the x-axis.
 *
 * @param cub Pointer to the t_Cub3d structure containing program context
 * and data.
 */
static void	get_step_x(t_Cub3d *cub)
{
	if (cub->cam->raydir_x < 0)
	{
		cub->cam->step_x = -1;
		cub->cam->side_dist_x =
			(cub->player->pos_x - cub->cam->map_x) * cub->cam->delta_dist_x;
	}
	else
	{
		cub->cam->step_x = 1;
		cub->cam->side_dist_x =
			(cub->cam->map_x + 1.0 - cub->player->pos_x) *
			cub->cam->delta_dist_x;
	}
}

/**
 * @brief Perform raycasting for each column in the screen.
 *
 * The gameloop function simulates the process of raycasting for each column
 * on the screen. In a typical first-person game, players perceive depth and
 * distance based on their field of view (FOV). The FOV is translated into
 * horizontal angles for each column, representing the directions of rays being
 * cast. The FOV's angle can influence the level of immersion and realism in the
 * scene.
 *
 * For every column on the screen, this function calculates the angle of the
 * ray's direction and maps that angle to a corresponding position in the
 * player's view. The ray's direction determines its movement in the horizontal
 * 2D map, allowing the ray to detect collisions with walls and render the 3D
 * environment.
 *
 * Throughout this process, the function computes step values and side distances
 * based on the ray direction. It also checks if the ray intersects with a wall
 * (hit), which signals the presence of an obstacle along the ray's path.
 * Several parameters are determined to ensure accurate rendering of wall slices
 * on the screen. These parameters include the perpendicular distance to the
 * wall, the height of the wall slice on the screen, and the starting and ending
 * positions for drawing the wall slice.
 *
 * @note Depending on the game's design, vertical raycasting might be unnecessary if
 * the camera's vertical movement is constrained. In such scenarios, eliminating
 * vertical raycasting can optimize performance while still delivering a
 * convincing 3D effect.
 *
 * @param cub Pointer to the t_Cub3d structure containing program context and
 * data.
 */
int	gameloop(t_Cub3d *cub)
{
	int		x;
	//bool	hit;
	//ATIVAR HIT FLAG E IF L:126/138/139
	x = 0;
	// UPDATE GAME STATE (PLAYER MOVEMENT, ETC)
	while (x < WINDOW_X)
	{
		//hit = false;
		cub->cam->camera_x = 2 * x / (double)WINDOW_X - 1;
		cub->cam->raydir_x =
			cub->player->dir_x + cub->player->fov_x *cub->cam->camera_x;
		cub->cam->raydir_y =
			cub->player->dir_y + cub->player->fov_y * cub->cam->camera_x; // This one is if we want to include complex vertical camera movement, jumping, etc...
		cub->cam->map_x = (int)cub->player->pos_x;
		cub->cam->map_y = (int)cub->player->pos_y;
		cub->cam->delta_dist_x = ft_abs(1 / cub->cam->raydir_x);
		cub->cam->delta_dist_y = ft_abs(1 / cub->cam->raydir_y); // This one is if we want to include complex vertical camera movement, jumping, etc...
		get_step_x(cub);
		get_step_y(cub);  // This one is if we want to include complex vertical camera movement, jumping, etc...
		//if (cub->map->matrix[cub->cam->map_y][cub->cam->map_x] == '1')
			//hit = true;

		// Calculate the perpendicular distance to the wall
        // ... (calculate perp_wall_dist)

        // Calculate the height of the wall slice on the screen
        // ... (calculate line_height)

        // Calculate the starting and ending positions to draw the wall slice
        // ... (calculate draw_start and draw_end)

        // ... (visualize the wall slice using Bresenham's line drawing)

		x++;
	}
	// RENDER SCENE
	return (0);
}
