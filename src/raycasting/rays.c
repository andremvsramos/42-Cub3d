/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:45:15 by andvieir          #+#    #+#             */
/*   Updated: 2023/09/14 12:09:28 by andvieir         ###   ########.fr       */
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
void	init_rays(t_Cub3d *cub, t_CameraConfig *cam, int x)
{
	cam->camera_x = 2 * x / (double)WINDOW_X - 1;
	cam->raydir_x = cub->player->dir_x + cam->plane_x * cam->camera_x;
	cam->raydir_y = cub->player->dir_y + cam->plane_y * cam->camera_x;
	cam->map_x = floor(cub->player->pos_x);
	cam->map_y = floor(cub->player->pos_y);
/* 	if (!cam->raydir_x)
		cam->ddist_x = 1e30;
	else */
		cam->ddist_x = fabs(1 / cam->raydir_x);
	/* if (!cam->raydir_y)
		cam->ddist_y = 1e30;
	else */
		cam->ddist_y = fabs(1 / cam->raydir_y);
}

void	draw_rays(t_Cub3d *cub)
{
	int				x;
	int				y;
	unsigned int	color;
	t_CameraConfig *cam;

	cam = cub->cam;
	x = 0;
	cam_utils_init(cam);
	render_ceilling_floor(cub);
	while (x < WINDOW_X)
	{
		init_rays(cub, cam, x);
		step_calculation(cam, cub->player);
		apply_dda(cam, cub->map);
		calculate_wall_height(cam);
		if (cam->side == 1)
			color = 0x98FB98;
		else
			color = 0x01796F;
		y = cam->draw_start;
		while (y < cam->draw_end)
		{
			my_mlx_pixel_put(cub->img, x, y, color);
			y++;
		}
		x++;
	}
	//draw_minimap(cub);
	//mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img->img_ptr, 0, 0);
	//mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr,
	//	cub->minimap->img->img_ptr, 0, 0);
}
