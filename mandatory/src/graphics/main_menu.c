/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:03:05 by andvieir          #+#    #+#             */
/*   Updated: 2023/09/27 15:57:11 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void	update_button(t_Cub3d *c, t_ImageControl *i, int p, char b)
{
	mlx_destroy_image(c->mlx_ptr, i->img_ptr);
	if (b == 's')
	{
		if (p)
			setup_menu(c, c->main->start, "./sprites/Menu/start_01.xpm");
		else
			setup_menu(c, c->main->start, "./sprites/Menu/start_00.xpm");
		mlx_put_image_to_window(c->mlx_ptr, c->win_ptr, i->img_ptr,
		(WINDOW_X / 2) - i->width / 2, ((WINDOW_Y - 100) / 2) - i->height);
	}
	else if (b == 'q')
	{
		if (p)
			setup_menu(c, c->main->quit, "./sprites/Menu/quit_01.xpm");
		else
			setup_menu(c, c->main->quit, "./sprites/Menu/quit_00.xpm");
		mlx_put_image_to_window(c->mlx_ptr, c->win_ptr, i->img_ptr,
		(WINDOW_X / 2) - i->width / 2, ((WINDOW_Y + 450) / 2) - i->height);
	}
}

int	button_mo(t_Cub3d *cub, t_ImageControl *i, char b)
{
	mlx_mouse_get_pos(cub->mlx_ptr, cub->win_ptr, &cub->mouse_x, &cub->mouse_y);
	if (b == 's')
	{
		if ((cub->mouse_x >= (WINDOW_X / 2) - i->width / 2)
		&& (cub->mouse_x <= (WINDOW_X / 2) + i->width / 2)
		&& (cub->mouse_y >= ((WINDOW_Y - 100) / 2) - i->height)
		&& (cub->mouse_y <= (WINDOW_Y - 100) / 2))
		return (1);
	}
	else if (b == 'q')
	{
		if ((cub->mouse_x >= (WINDOW_X / 2) - i->width / 2)
			&& (cub->mouse_x <= (WINDOW_X / 2) + i->width / 2)
			&& (cub->mouse_y >= ((WINDOW_Y + 450) / 2) - i->height)
			&& (cub->mouse_y <= (WINDOW_Y + 450) / 2))
			return (1);
	}
	return (0);
}

void setup_menu(t_Cub3d *cub, t_TextureSetup *tex, char *file)
{
	load_xpm(cub, tex->img, file);
	(void)tex->path;
	tex->img->addr = mlx_get_data_addr(tex->img->img_ptr, &tex->img->bpp,
		&tex->img->len, &tex->img->endian);
}

int	start_menu(t_Cub3d *cub)
{
	t_Menu *m;

	cub->main = ft_calloc(1, sizeof(t_Menu));
	m = cub->main;
	cub->menu_active = true;
	m->start = ft_calloc(1, sizeof(t_TextureSetup));
	m->start->img = ft_calloc(1, sizeof(t_ImageControl));
	m->quit = ft_calloc(1, sizeof(t_TextureSetup));
	m->quit->img = ft_calloc(1, sizeof(t_ImageControl));
	setup_menu(cub, m->start, "./sprites/Menu/start_00.xpm");
	setup_menu(cub, m->quit, "./sprites/Menu/quit_00.xpm");
	cub->menu_ok = true;
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, m->start->img->img_ptr,
		(WINDOW_X / 2) - m->start->img->width / 2,
		((WINDOW_Y - 100) / 2) - m->start->img->height);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, m->quit->img->img_ptr,
		(WINDOW_X / 2) - m->quit->img->width / 2,
		((WINDOW_Y + 450) / 2) - m->quit->img->height);
	return (0);
}
