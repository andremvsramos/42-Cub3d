/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_gun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:53:35 by andvieir          #+#    #+#             */
/*   Updated: 2023/09/27 12:03:30 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void	gun_new_image(t_Cub3d *cub, t_PlayerConfig *p)
{
	mlx_destroy_image(cub->mlx_ptr, p->gun_sprite->img->img_ptr);
	p->gun_sprite->img->img_ptr = mlx_new_image(cub->mlx_ptr, 555, 530);
	p->gun_sprite->img->addr = mlx_get_data_addr(p->gun_sprite->img->img_ptr,
		&p->gun_sprite->img->bpp, &p->gun_sprite->img->len,
		&p->gun_sprite->img->endian);
}

void	draw_gun(t_PlayerConfig *p, int x, int y)
{
	int color;

	color = 0;

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
}

int	player_gun(t_Cub3d *cub, t_PlayerConfig *p)
{
	int	color;
	int	x;
	int	y;

	p->gun = ft_calloc(1, sizeof(t_TextureSetup));
	(void)p->gun->path;
	p->gun->img = ft_calloc(1, sizeof(t_ImageControl));
	setup_menu(cub, p->gun, "./sprites/Gun_Sprites/g_00.xpm");
	p->gun_sprite = ft_calloc(1, sizeof(t_TextureSetup));
	if (!p->gun_sprite)
		return (1);
	(void)p->gun_sprite->path;
	p->gun_sprite->img = ft_calloc(1, sizeof(t_ImageControl));
	if (!p->gun_sprite->img)
		return (1);
	p->gun_sprite->img->img_ptr = mlx_new_image(cub->mlx_ptr,
		555, 530);
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
	return (0);
}
