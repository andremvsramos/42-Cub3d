/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:45:15 by andvieir          #+#    #+#             */
/*   Updated: 2023/09/05 15:25:26 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void	ray_per_colum(t_Cub3d *cub, t_CameraConfig *cam, int x)
{
	cam->camera_x = 2 * x / (double)WINDOW_X - 1;
	cam->raydir_x = cub->player->dir_x + cam->plane_x * cam->camera_x;
	cam->raydir_y = cub->player->dir_y + cam->plane_y * cam->camera_x;
}

void	ray_map_pos(t_Cub3d *cub, t_CameraConfig *cam)
{
	cam->map_x = (int)cub->player->pos_x;
	cam->map_y = (int)cub->player->pos_y;
}

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
