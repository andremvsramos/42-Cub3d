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

static unsigned int	get_color(int color[256][256][256])
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

void	my_mlx_pixel_put(t_ImageControl *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

static void	render_ceilling_floor(t_Cub3d *cub)
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
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img->img_ptr, 0, 0);
}

/**
 * @brief Initialize the graphics context and camera for rendering in the Cub3D
 * application.
 *
 * The `graphics` function is responsible for setting up the graphics context of
 * the Cub3D application. It first calls the `check_tex_validity` function to
 * validate the texture files. If the texture files are valid, the function
 * initializes the mlx library using `mlx_init` and creates a new window with a
 * specified resolution using `mlx_new_window`. Additionally, memory is
 * allocated for a `t_ImageControl` structure to manage the application's image
 * data. The image structure is initialized with `mlx_new_image`, and its
 * attributes are obtained using `mlx_get_data_addr`. The function then
 * initializes the camera using the `camera_init` function. If any
 * initialization step fails or the texture files are invalid, the function
 * returns 1; otherwise, it returns 0 to indicate a successful graphics
 * context setup.
 *
 * @param cub Pointer to the `t_Cub3d` structure containing program context and
 * data.
 * @return Returns 0 if the graphics context initializes successfully, or 1 if
 * there's an error during setup.
 */
int	graphics(t_Cub3d *cub)
{
	cub->mlx_ptr = mlx_init();
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, WINDOW_X, WINDOW_Y, "CUB3D");
	cub->img = ft_calloc(1, sizeof(t_ImageControl));
	cub->img->img_ptr = mlx_new_image(cub->mlx_ptr, WINDOW_X, WINDOW_Y);
	cub->img->addr = mlx_get_data_addr(cub->img->img_ptr, &cub->img->bpp, &cub->img->len, &cub->img->endian);
	render_ceilling_floor(cub);
	set_player_position(cub);
	if (check_tex_validity(cub))
		return (1);
	if (camera_init(cub))
		return (1);
	cub->graphics_ok = true;
	return (0);
}

/**
 * @brief Initialize essential components and start the Cub3D application.
 *
 * The `boot` function serves as the entry point to the Cub3D application. It
 * orchestrates the initialization of essential components such as the graphics
 * context and event hooks. First, it calls the `graphics` function to set up the
 * graphics context, including creating the main application window and image
 * control structures. If the graphics initialization fails, the function
 * returns 1 to indicate an error. Next, it calls the `hook_events` function to
 * set up event hooks for keyboard inputs and window closing. If both
 * initialization steps succeed, the function starts the main game loop by
 * registering the `gameloop` function via `mlx_loop_hook`. It then enters the
 * event loop using `mlx_loop`, which continuously updates the game state and
 * renders the scene. The function does not return until the application is
 * exited.
 *
 * @param cub Pointer to the `t_Cub3d` structure containing program context
 * and data.
 * @return Returns 0 if the application boots successfully.
 */
int	boot(t_Cub3d *cub)
{
	if (graphics(cub))
		return (1);
	hook_events(cub);
	mlx_loop_hook(cub->mlx_ptr, &gameloop, cub);
	//draw_2d_map(cub);
	mlx_loop(cub->mlx_ptr);
	return (0);
}
