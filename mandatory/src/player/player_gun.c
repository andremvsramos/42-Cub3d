/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_gun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:53:35 by andvieir          #+#    #+#             */
/*   Updated: 2023/09/27 16:14:06 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

static int	check_tolerance(int color, char c)
{
	int	r;
	int	g;
	int	b;


	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	if (c == 'b')
	{
		if (abs(r - 0x00) > 120 ||
			abs(g - 0x00) > 120 ||
			abs(b - 0x00) > 120)
			return (0);
	}
	else if (c == 'p')
	{
		if (abs(r - 0xFF) > 120 ||
			abs(g - 0) > 120 ||
			abs(b - 0xFF) > 120)
			return (0);
	}
	return (1);
}

void	draw_gun(t_Cub3d *cub, t_PlayerConfig *p, int x, int y)
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
			if (!check_tolerance(color, 'p'))
				my_mlx_pixel_put(cub->img, WINDOW_X - 760 + x,
				WINDOW_Y - 530 + y, color);
			y++;
		}
		x++;
	}
}

void	draw_crosshair(t_Cub3d *cub, t_PlayerConfig *p, int x, int y)
{
	int	color;

	color = 0;
	x = 0;
	while (x < p->crosshair->img->width)
	{
		y = 0;
		while (y < p->crosshair->img->height)
		{
			color = my_mlx_pixel_get(p->crosshair->img, x, y);
			if (!check_tolerance(color, 'b'))
				my_mlx_pixel_put(cub->img, (WINDOW_X / 2) - (p->crosshair->img->width / 2) + x,
				(WINDOW_Y / 2) - (p->crosshair->img->height / 2) + y, color);
			y++;
		}
		x++;
	}
}

int	player_gun(t_Cub3d *cub, t_PlayerConfig *p)
{
	p->gun = ft_calloc(1, sizeof(t_TextureSetup));
	(void)p->gun->path;
	p->gun->img = ft_calloc(1, sizeof(t_ImageControl));
	setup_menu(cub, p->gun, "./sprites/Gun_Sprites/g_00.xpm");
	p->crosshair = ft_calloc(1, sizeof(t_TextureSetup));
	(void)p->crosshair->path;
	p->crosshair->img = ft_calloc(1, sizeof(t_ImageControl));
	setup_menu(cub, p->crosshair, "./sprites/Gun_Sprites/crosshair.xpm");
	cub->gun_ok = true;
	return (0);
}
