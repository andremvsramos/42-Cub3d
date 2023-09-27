/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_gun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:53:35 by andvieir          #+#    #+#             */
/*   Updated: 2023/09/27 23:42:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

/**
 * @brief Check color tolerance for pixel color matching.
 *
 * The `check_tolerance` function checks whether a given pixel color matches
 * a predefined tolerance level for color channels (red, green, and blue).
 * It is used to filter out specific colors ('p' for pink or 'b' for black)
 * from an image.
 *
 * @param color The pixel color to be checked.
 * @param c A character indicating the color filter to apply ('p' for pink or
 * 'b' for black).
 * @return 1 if the color passes the tolerance check, 0 otherwise.
 */
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
		if (abs(r - 0x00) > 120
			|| abs(g - 0x00) > 120
			|| abs(b - 0x00) > 120)
			return (0);
	}
	else if (c == 'p')
	{
		if (abs(r - 0xFF) > 120
			|| abs(g - 0) > 120
			|| abs(b - 0xFF) > 120)
			return (0);
	}
	return (1);
}

/**
 * @brief Draw the player's gun on the game screen.
 *
 * The `draw_gun` function is responsible for rendering the player's gun image
 * onto the game screen with color filtering. It extracts the gun image's pixel
 * colors, applies a color filter for pink ('p'), and renders the filtered
 * image.
 *
 * @param cub Pointer to the Cub3D game configuration structure.
 * @param p Pointer to the PlayerConfig structure containing player information.
 * @param x The starting horizontal position for rendering the gun image.
 * @param y The starting vertical position for rendering the gun image.
 */
void	draw_gun(t_Cub3d *cub, t_PlayerConfig *p, int x, int y)
{
	int	color;

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

/**
 * @brief Draw a crosshair on the game screen.
 *
 * The `draw_crosshair` function renders a crosshair image onto the game screen
 * with color filtering. It extracts the crosshair image's pixel colors, applies
 * a color filter for black ('b'), and renders the filtered image at the center
 * of the game screen.
 *
 * @param cub Pointer to the Cub3D game configuration structure.
 * @param p Pointer to the PlayerConfig structure containing player information.
 * @param x The starting horizontal position for rendering the crosshair image.
 * @param y The starting vertical position for rendering the crosshair image.
 */
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
				my_mlx_pixel_put(cub->img,
					(WINDOW_X / 2) - (p->crosshair->img->width / 2) + x,
					(WINDOW_Y / 2) - (p->crosshair->img->height / 2) + y,
					color);
			y++;
		}
		x++;
	}
}

/**
 * @brief Initialize the player's gun and crosshair.
 *
 * The `player_gun` function initializes the player's gun and crosshair images
 * by allocating memory for texture setups and image controls. It loads the gun
 * and crosshair images from file paths and sets up the necessary data
 * structures.
 *
 * @param cub Pointer to the Cub3D game configuration structure.
 * @param p Pointer to the PlayerConfig structure containing player information.
 * @return 0 on successful initialization.
 */
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
