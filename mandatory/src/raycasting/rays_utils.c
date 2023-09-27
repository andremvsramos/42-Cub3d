/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:17:21 by marvin            #+#    #+#             */
/*   Updated: 2023/09/07 14:17:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

/**
 * @brief Determine the direction of the wall hit by the ray.
 *
 * The `get_wall_direction` function determines the direction of the wall hit
 * by the ray. It assigns a specific code to `wall_dir` based on whether the ray
 * hits a wall in the north, south, east, or west direction. This information is
 * useful for texture mapping and rendering walls correctly.
 *
 * @param c Pointer to the `t_CameraConfig` structure containing camera
 * configuration data.
 */
void	get_wall_direction(t_MapConfig *m, t_CameraConfig *c)
{
	if (c->hit && m->matrix[c->map_y][c->map_x] == '9')
		c->wall_dir = 9;
	else if (c->side == 1)
	{
		if (c->raydir_y < 0)
			c->wall_dir = 1;
		else
			c->wall_dir = 2;
	}
	else
	{
		if (c->raydir_x < 0)
			c->wall_dir = 3;
		else
			c->wall_dir = 4;
	}
}

/**
 * @brief Calculate the height and rendering parameters for a wall segment.
 *
 * The `calculate_wall_height` function is responsible for determining the height
 * of a wall segment on the screen and setting up the rendering parameters for
 * that segment. This function calculates the perpendicular wall distance
 * (`perp_wd`) based on the camera's view and distance to the wall. It then
 * calculates the `line_height` which represents the height of the wall on the
 * screen. The `draw_start` and `draw_end` values are set to specify where the
 * wall segment should be drawn within the screen's vertical space.
 *
 * @param cam Pointer to the `t_CameraConfig` structure containing camera
 * configuration data.
 */
void	calculate_wall_height(t_CameraConfig *cam)
{
	if (cam->side == 0)
		cam->perp_wd = (cam->s_dist_x - cam->ddist_x);
	else
		cam->perp_wd = (cam->s_dist_y - cam->ddist_y);
	if (cam->perp_wd)
		cam->line_height = (int)(WINDOW_Y / cam->perp_wd);
	else
		cam->line_height = WINDOW_Y;
	cam->draw_start = -cam->line_height / 2 + WINDOW_Y / 2;
	if (cam->draw_start < 0)
		cam->draw_start = 0;
	cam->draw_end = cam->line_height / 2 + WINDOW_Y / 2;
	if (cam->draw_end >= WINDOW_Y)
		cam->draw_end = WINDOW_Y - 1;
}

/**
 * @brief Apply the Digital Differential Analyzer (DDA) algorithm to find the
 * first wall hit.
 *
 * The `apply_dda` function applies the Digital Differential Analyzer (DDA)
 * algorithm to trace a ray and find the point where it first intersects with a
 * wall in the game map. It iteratively calculates the horizontal and vertical
 * distances to the next potential wall hit (`s_dist_x` and `s_dist_y`) and
 * updates the current map position (`map_x` and `map_y`) along with the ray
 * step direction (`step_x` and `step_y`). The `side` variable is set to 0 for
 * horizontal hits and 1 for vertical hits.
 *
 * @param cam Pointer to the `t_CameraConfig` structure containing camera
 * configuration data.
 * @param m Pointer to the `t_MapConfig` structure containing game map data.
 */
void	apply_dda(t_CameraConfig *cam, t_MapConfig *m)
{
	while (!cam->hit)
	{
		if (cam->s_dist_x < cam->s_dist_y)
		{
			cam->s_dist_x += cam->ddist_x;
			cam->map_x += cam->step_x;
			cam->side = 0;
		}
		else
		{
			cam->s_dist_y += cam->ddist_y;
			cam->map_y += cam->step_y;
			cam->side = 1;
		}
		if (m->matrix[cam->map_y][cam->map_x] == '1'
			|| m->matrix[cam->map_y][cam->map_x] == '9')
			cam->hit = 1;
	}
}

/**
 * Calculate step and initial side distance values for raycasting.
 *
 * This function calculates the step values (step_x and step_y) for raycasting
 * and initializes the side distance values (s_dist_x and s_dist_y) based on the
 * direction of the camera's ray (raydir_x and raydir_y) and the player's
 * position. It determines whether the ray is moving left or right in the X
 * direction and up or down in the Y direction and sets the step and side
 * distance values accordingly.
 *
 * @param cam A pointer to the CameraConfig structure.
 * @param p A pointer to the PlayerConfig structure representing the player's
 * position.
 */
void	step_calculation(t_CameraConfig *cam, t_PlayerConfig *p)
{
	cam->hit = 0;
	if (cam->raydir_x < 0)
	{
		cam->step_x = -1;
		cam->s_dist_x = (p->pos_x - cam->map_x) * cam->ddist_x;
	}
	else
	{
		cam->step_x = 1;
		cam->s_dist_x = (cam->map_x + 1.0 - p->pos_x) * cam->ddist_x;
	}
	if (cam->raydir_y < 0)
	{
		cam->step_y = -1;
		cam->s_dist_y = (p->pos_y - cam->map_y) * cam->ddist_y;
	}
	else
	{
		cam->step_y = 1;
		cam->s_dist_y = (cam->map_y + 1.0 - p->pos_y) * cam->ddist_y;
	}
}
