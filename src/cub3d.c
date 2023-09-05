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

static void	calculate_wall_height(t_CameraConfig *cam, int wall_height_px)
{
	cam->line_height = (int)(wall_height_px / cam->perp_wd);
	cam->draw_start = -cam->line_height / 2 + WINDOW_Y / 2;
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
		if (m->matrix[cam->map_y][cam->map_x] == '1')
			cam->hit = 1;
	}
	if (cam->side == 0)
		cam->perp_wd = cam->s_dist_x - cam->ddist_x;
	else
		cam->perp_wd = cam->s_dist_y - cam->ddist_y;
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
	int				x;
	int				y;
	unsigned int	color;
	t_CameraConfig *cam;

	cam = cub->cam;
	x = 0;
	cam_utils_init(cam);
	while (x < WINDOW_X)
	{
		ray_per_colum(cub, cam, x);
		ray_map_pos(cub, cam);
		cam->s_dist_x = 0;
		cam->s_dist_y = 0;
		ray_delt_dist(cam);
		cam->step_x = 0;
		cam->step_y = 0;
		cam->hit = 0;
		cam->side = 0;
		cam->perp_wd = 0;
		step_calculation(cam, cub->player);
		apply_dda(cam, cub->map);
		calculate_wall_height(cam, 300);
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
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img->img_ptr, 0, 0);
    return (0);
}
