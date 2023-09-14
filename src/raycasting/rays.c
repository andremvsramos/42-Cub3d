/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:45:15 by andvieir          #+#    #+#             */
/*   Updated: 2023/09/15 00:39:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

/**
 * @brief Initialize ray properties for a specific column of the screen.
 *
 * The `init_rays` function initializes the properties of a ray for a specific
 * column of the screen during the raycasting process. It calculates the
 * camera's position on the screen (`camera_x`), the ray's direction (`raydir_x`
 * and `raydir_y`), and the initial map position (`map_x` and `map_y`).
 * Additionally, it calculates the delta distance (`ddist_x` and `ddist_y`)
 * required to move from one grid cell to the next in both the horizontal and
 * vertical directions.
 *
 * @param cub Pointer to the `t_Cub3d` structure containing program context and
 * data.
 * @param cam Pointer to the `t_CameraConfig` structure containing camera
 * configuration data.
 * @param x The current screen column being processed.
 */
void	init_rays(t_Cub3d *cub, t_CameraConfig *cam, int x)
{
	cam->camera_x = 2 * x / (double)WINDOW_X - 1;
	cam->raydir_x = cub->player->dir_x + cam->plane_x * cam->camera_x;
	cam->raydir_y = cub->player->dir_y + cam->plane_y * cam->camera_x;
	cam->map_x = floor(cub->player->pos_x);
	cam->map_y = floor(cub->player->pos_y);
	if (!cam->raydir_x)
		cam->ddist_x = 1e30;
	else
		cam->ddist_x = fabs(1 / cam->raydir_x);
	if (!cam->raydir_y)
		cam->ddist_y = 1e30;
	else
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
		get_wall_direction(cub->cam);
		if (cam->wall_dir == 1)
			color = 0x98FB98;
		else if (cam->wall_dir == 2)
			color = 0x01796F;
		else if (cam->wall_dir == 3)
			color = 0x02996F;
		else if (cam->wall_dir == 4)
			color = 0x02ABD9;
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
