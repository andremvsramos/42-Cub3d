/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_gun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:53:35 by andvieir          #+#    #+#             */
/*   Updated: 2023/09/22 20:02:04 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void	draw_gun(t_Cub3d *cub, t_PlayerConfig *p, int x, int y)
{
	int color;

	(void)cub;
	color = 0;
	/* mlx_destroy_image(cub->mlx_ptr, p->gun_sprite->img->img_ptr);
	p->gun_sprite->img->img_ptr = mlx_new_image(cub->mlx_ptr, 1280, 1181);
	p->gun_sprite->img->addr = mlx_get_data_addr(p->gun_sprite->img->img_ptr,
		&p->gun_sprite->img->bpp, &p->gun_sprite->img->len,
		&p->gun_sprite->img->endian); */
	x = 0;
	while (x < p->gun->img->width)
	{
		y = 0;
		while (y < p->gun->img->height)
		{
			color = my_mlx_pixel_get(p->gun->img, x, y);
			if (color != 0xFF00FF)
				my_mlx_pixel_put(p->gun_sprite->img, x, y, color);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr,
	p->gun_sprite->img->img_ptr,
	WINDOW_X - p->gun_sprite->img->width,
	WINDOW_Y - p->gun_sprite->img->height);
}

int	player_gun(t_Cub3d *cub, t_PlayerConfig *p)
{
	int	color;
	int	x;
	int	y;

	p->gun = ft_calloc(1, sizeof(t_TextureSetup));
	if (!p->gun)
		return (1);
	(void)p->gun->path;
	p->gun->img = ft_calloc(1, sizeof(t_ImageControl));
	if (!p->gun->img)
		return (1);
	setup_menu(cub, p->gun, "./sprites/Gun Sprites/g_00.xpm");\
	p->gun_sprite = ft_calloc(1, sizeof(t_TextureSetup));
	if (!p->gun_sprite)
		return (1);
	(void)p->gun_sprite->path;
	p->gun_sprite->img = ft_calloc(1, sizeof(t_ImageControl));
	if (!p->gun_sprite->img)
		return (1);
	p->gun_sprite->img->img_ptr = mlx_new_image(cub->mlx_ptr,
		1280, 1181);
	p->gun_sprite->img->addr = mlx_get_data_addr(p->gun_sprite->img->img_ptr,
		&p->gun_sprite->img->bpp, &p->gun_sprite->img->len,
		&p->gun_sprite->img->endian);
	x = 0;
	while (x < p->gun->img->width)
	{
		y = 0;
		while (y < p->gun->img->height)
		{
			color = my_mlx_pixel_get(p->gun->img, x, y);
			if (color != 0xFF00FF)
				my_mlx_pixel_put(p->gun_sprite->img, x, y, color);
			y++;
		}
		x++;
	}
	/* mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr,
	p->gun_sprite->img->img_ptr, WINDOW_X - p->gun->img->width,
	WINDOW_Y - p->gun->img->height); */
	return (0);
}
