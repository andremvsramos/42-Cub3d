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

/* static int	mlx_pixel_get(t_ImageControl *img, int x, int y)\
{
	char *dst = img->addr + (y * img->width * (img->bpp / 8)) + (x * (img->bpp / 8));
	unsigned int color = *(unsigned int *)dst;
	return color;
} */

/* static void	calculate_wall_height(t_CameraConfig *cam, int wall_height_px)
{
	cam->line_height = (int)(wall_height_px / cam->perp_wd);
	cam->draw_start = cam->line_height / 2 + WINDOW_Y / 2;
	if (cam->draw_start < 0)
		cam->draw_start = 0;
	cam->draw_end = cam->line_height / 2 + WINDOW_Y / 2;
	if (cam->draw_end >= WINDOW_Y)
		cam->draw_end = WINDOW_Y - 1;
}

static void	apply_dda(t_CameraConfig *cam, t_MapConfig *m)
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
		if (cam->map_x >= 0 && cam->map_x < m->max_line_len + 1
			&& cam->map_y >= 0 && cam->map_y < m->n_lines + 1)
		{
			if (m->matrix[cam->map_y][cam->map_x] == '1')
				cam->hit = 1;
		}
	}
	if (cam->side == 0)
	{
		cam->perp_wd = (cam->map_x - cam->i_ray_x + (1 - cam->step_x) / 2)
			/ cam->raydir_x;
	}
	else
	{
		cam->perp_wd = (cam->map_y - cam->i_ray_y + (1 - cam->step_y) / 2)
			/ cam->raydir_y;
	}
}

static void	step_calculation(t_CameraConfig *cam, t_PlayerConfig *p)
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

int	gameloop(t_Cub3d *cub)
{
	int	x;
	int	y;
	t_CameraConfig *cam;

	cam = cub->cam;
	x = 0;
	while (x < WINDOW_X)
	{
		cam->camera_x = 2 * x / (double)WINDOW_X - 1;
		cam->raydir_x = cub->player->dir_x + cam->plane_x * cam->camera_x;
		cam->raydir_y = cub->player->dir_y + cam->plane_y * cam->camera_x;

		cam->map_x = (int)cub->player->pos_x;
		cam->map_y = (int)cub->player->pos_y;

		cam->ddist_x = fabs(1 / cam->raydir_x);
		cam->ddist_y = fabs(1 / cam->raydir_y);

		cam_utils_init(cam, cub->player);
		step_calculation(cam, cub->player);
		apply_dda(cam, cub->map);
		calculate_wall_height(cam, 150);
		y = cam->draw_start;
		while (y < cam->draw_end)
		{
			mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr,
				cub->map->tex_north->xpm, x, y);
			//mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, x, y, 0xFFFFFF);
			y++;
		}
		x++;
	}
    return (0);
} */
