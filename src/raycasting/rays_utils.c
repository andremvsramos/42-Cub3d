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

/* static int	mlx_pixel_get(t_ImageControl *img, int x, int y)\
{
	char *dst = img->addr + (y * img->width * (img->bpp / 8)) + (x * (img->bpp / 8));
	unsigned int color = *(unsigned int *)dst;
	return color;
} */

/**
 * Calculate the height and rendering boundaries for a wall.
 *
 * This function calculates the height of a wall and the rendering boundaries
 * based on the perpendicular distance (`perp_wd`) from the camera to the wall.
 * It sets the `line_height` to determine how tall the wall should be rendered
 * on the screen. It also calculates `draw_start` and `draw_end` to define the
 * vertical range for rendering the wall on the screen.
 *
 * @param cam A pointer to the CameraConfig structure.
 */
void	calculate_wall_height(t_CameraConfig *cam)
{
	if (cam->perp_wd)
		cam->line_height = (int)(500 / cam->perp_wd);
	else
		cam->line_height = cam->perp_wd;
	cam->draw_start = -cam->line_height / 2 + WINDOW_Y / 2;
	if (cam->draw_start < 0)
		cam->draw_start = 0;
	cam->draw_end = cam->line_height / 2 + WINDOW_Y / 2;
	if (cam->draw_end >= WINDOW_Y)
		cam->draw_end = WINDOW_Y - 1;
}

/**
 * Apply the Digital Differential Analyzer (DDA) algorithm to determine the first
 * wall hit by a ray.
 *
 * This function applies the Digital Differential Analyzer (DDA) algorithm to
 * determine the point of intersection between a ray cast from the camera and
 * the game map. It calculates the distance to the first wall hit, the map cell
 * coordinates where the hit occurs, and whether the hit is on a horizontal or
 * vertical wall. It updates the camera configuration accordingly.
 *
 * @param cam A pointer to the CameraConfig structure.
 * @param m A pointer to the MapConfig structure representing the game map.
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
		if (m->matrix[cam->map_y][cam->map_x] == '1')
			cam->hit = 1;
	}
	if (cam->side == 0)
		cam->perp_wd = cam->s_dist_x - cam->ddist_x;
	else
		cam->perp_wd = cam->s_dist_y - cam->ddist_y;
}

/**
 * Calculate step and initial side distance values for raycasting.
 *
 * This function calculates the step values (step_x and step_y) for raycasting
 * and initializes the side distance values (s_dist_x and s_dist_y) based on the
 * direction of the camera's ray (raydir_x and raydir_y) and the player's position.
 * It determines whether the ray is moving left or right in the X direction and up
 * or down in the Y direction and sets the step and side distance values accordingly.
 *
 * @param cam A pointer to the CameraConfig structure.
 * @param p A pointer to the PlayerConfig structure representing the player's position.
 */
void	step_calculation(t_CameraConfig *cam, t_PlayerConfig *p)
{
	if (cam->raydir_x < 0)
	{
		cam->step_x = -1;
		cam->s_dist_x = (p->pos_x - cam->map_x) * cam->ddist_x;
	}
	else
	{
		cam->step_x = 1;
		cam->s_dist_x = (cam->map_x + 1 - p->pos_x) * cam->ddist_x;
	}
	if (cam->raydir_y < 0)
	{
		cam->step_y = -1;
		cam->s_dist_y = (p->pos_y - cam->map_y) * cam->ddist_y;
	}
	else
	{
		cam->step_y = 1;
		cam->s_dist_y = (cam->map_y + 1 - p->pos_y) * cam->ddist_y;
	}
}
