/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Untitled-1                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:15:12 by marvin            #+#    #+#             */
/*   Updated: 2023/08/19 19:15:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

/**
 * Get a color code from a 256x256x256 color array.
 *
 * This function takes a three-dimensional color array and searches for the
 * first non-zero element (color). It then converts the RGB values to a
 * hexadecimal color code and returns it. If no non-zero color is found, it
 * returns 0 (black).
 *
 * @param color A 256x256x256 array representing colors (RGB format).
 * @return An unsigned integer representing the color code in hexadecimal format
 * (0xRRGGBB).
 */
static int	get_color(int color[256][256][256])
{
	int	r;
	int	g;
	int	b;

	r = 0;
	while (r < 256)
	{
		g = 0;
		while (g < 256)
		{
			b = 0;
			while (b < 256)
			{
				if (color[r][g][b])
					return (0x010000 * r + 0x000100 * g + b);
				b++;
			}
			g++;
		}
		r++;
	}
	return (0);
}

/**
 * Set a pixel color in an image.
 *
 * This function sets the color of a pixel at the specified (x, y) coordinates
 * in an image. It takes an image control structure (`img`), the (x, y) position
 * of the pixel, and the color value to set.
 *
 * @param img A pointer to the ImageControl structure representing the image.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param color The color value to set (in integer format).
 */
void	my_mlx_pixel_put(t_ImageControl *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

/**
 * Render the ceiling and floor of the game window.
 *
 * This function renders the ceiling and floor of the game window by setting
 * the pixel colors in the image buffer (`cub->img`) for the entire window area.
 * It uses the colors defined in the `cub->map` structure for the ceiling and
 * floor.
 *
 * @param cub A pointer to the Cub3d structure.
 */
void	render_ceilling_floor(t_Cub3d *cub)
{
	int				x;
	int				y;
	unsigned int	cc;
	unsigned int	fc;

	x = 0;
	cc = get_color(cub->map->ceilling_c);
	fc = get_color(cub->map->floor_c);
	while (x++ < WINDOW_X)
	{
		y = 0;
		while (y++ <= WINDOW_Y / 2)
			my_mlx_pixel_put(cub->img, x, y, cc);
		while (y < WINDOW_Y)
		{
			my_mlx_pixel_put(cub->img, x, y, fc);
			y++;
		}
	}
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr,
		cub->img->img_ptr, 0, 0);
}

/**
 * @brief Initializes the game graphics, assets, and core components.
 *
 * The `graphics` function plays a pivotal role in the Cub3D project by
 * setting up the entire game environment. It encompasses the initialization
 * of graphics components, the creation of the game window, and the setup of
 * essential assets and state variables.
 *
 * Specifically, this function handles the following tasks:
 *
 * - Initializes the camera configuration, essential for raycasting.
 * - Validates and loads all required textures and assets.
 * - Creates the game window using the MLX library with a specified size.
 * - Prepares the game's image buffer for rendering.
 * - Initializes the start menu, allowing players to begin or quit the game.
 * - Sets up the minimap, which provides an overview of the game map.
 * - Positions and renders the player's gun within the game view.
 * - Places the player character at the starting position.
 * - Converts loaded textures into formats suitable for rendering.
 *
 * If any of these initialization steps fail, the function returns an error code
 * (1) to indicate that there was an issue with the setup process. A return
 * value of 0 signifies that the graphics and game environment are successfully
 * set up and ready for gameplay.
 *
 * @param cub Pointer to the t_Cub3d structure, representing the game's context.
 * @return 0 if graphics initialization is successful, 1 if there are errors.
 */
int	graphics(t_Cub3d *cub)
{
	if (camera_init(cub))
		return (1);
	if (check_tex_validity(cub))
		return (1);
	cub->mlx_ptr = mlx_init();
	cub->img = ft_calloc(1, sizeof(t_ImageControl));
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, WINDOW_X, WINDOW_Y, "CUB3D");
	cub->img->img_ptr = mlx_new_image(cub->mlx_ptr, WINDOW_X, WINDOW_Y);
	cub->img->addr = mlx_get_data_addr(cub->img->img_ptr,
			&cub->img->bpp, &cub->img->len, &cub->img->endian);
	if (start_menu(cub))
		return (1);
	init_minimap(cub);
	player_gun(cub, cub->player);
	cub->graphics_ok = true;
	set_player_position(cub);
	if (convert_textures(cub))
		return (1);
	cub->files_ok = true;
	return (0);
}

/**
 * @brief Initialize essential components and start the Cub3D application.
 *
 * The `boot` function serves as the entry point to the Cub3D application. It
 * orchestrates the initialization of essential components, including the
 * graphics context, and event hooks. It calls the `graphics` function to set up
 * the graphics context, create the main application window, and initialize
 * image control structures. If the graphics initialization fails, the function
 * returns 1 to indicate an error. Otherwise, it returns 0 to indicate a
 * successful initialization. The `boot` function does not directly start the
 * game loop but prepares the application for rendering.
 *
 * @param cub Pointer to the `t_Cub3d` structure containing program context and
 * data.
 * @return Returns 0 if the application initialization is successful, or 1 if
 * there's an error during setup.
 */
int	boot(t_Cub3d *cub)
{
	if (graphics(cub))
		return (1);
	return (0);
}
