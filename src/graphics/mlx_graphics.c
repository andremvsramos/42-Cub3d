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
 * @brief Initialize texture setup data for a specific texture within the
 * Cub3D context.
 *
 * This function initializes the texture setup data for a specific texture
 * within the Cub3D context. It allocates memory for a t_ImageControl structure
 * to manage image data and initializes its members. If memory allocation fails
 * for any step, the function cleans up allocated resources, terminates the
 * program, and displays an error message.
 *
 * @param cub Pointer to the t_Cub3d structure containing
 * program context and data.
 * @param texture Pointer to the t_TextureSetup structure representing
 * the texture.
 * @return Returns 0 on success, or 1 on failure.
 */
static int	tex_setup(t_Cub3d *cub, t_TextureSetup *texture)
{
	texture->img = ft_calloc(1, sizeof(t_ImageControl));
	if (!texture->img)
		return (1);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, texture->xpm, WINDOW_X/2, WINDOW_Y/2);
	if (!texture->img->addr)
		return (1);
	return (0);
}

/**
 * @brief Initialize the graphics context for rendering in the Cub3D
 * application.
 *
 * The `graphics` function is responsible for setting up the graphics context of
 * the Cub3D application. It first calls the `check_tex_validity` function to
 * validate the texture files. If the texture files are valid, the function
 * initializes the mlx library using `mlx_init` and creates a new window with a
 * specified resolution using `mlx_new_window`. Additionally, memory is
 * allocated for an `t_ImageControl` structure to manage the application's image
 * data. The image structure is initialized with `mlx_new_image`, and its
 * attributes are obtained using `mlx_get_data_addr`. If any initialization step
 * fails or the texture files are invalid, the function returns 1; otherwise, it
 * returns 0 to indicate successful graphics context setup.
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
	cub->img->addr = mlx_get_data_addr(cub->img->img_ptr, &cub->img->bpp,
		&cub->img->len, &cub->img->endian);
	if (check_tex_validity(cub))
		return (1);
	cub->graphics_ok = true;
	if (tex_setup(cub, cub->map->tex_north) || tex_setup(cub, cub->map->tex_south)
		|| tex_setup(cub, cub->map->tex_west) || tex_setup(cub, cub->map->tex_east))
		return (1);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->map->tex_north->img->img_ptr, WINDOW_X/2, WINDOW_Y/2);/*
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->map->tex_south->img->img_ptr, WINDOW_X/2, WINDOW_Y/2);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->map->tex_west->img->img_ptr, WINDOW_X/2, WINDOW_Y/2);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->map->tex_east->img->img_ptr, WINDOW_X/2, WINDOW_Y/2); */
	return (0);
}

/**
 * @brief Initialize essential components and start the Cub3D application.
 *
 * The boot function serves as the entry point to the Cub3D application. It
 * orchestrates the initialization of essential components such as the graphics
 * context and event hooks. First, it calls the graphics function to set up the
 * graphics context, including creating the main application window and image
 * control structures. If the graphics initialization fails, the function
 * returns 1 to indicate an error. Next, it calls the hook_events function to
 * set up event hooks for keyboard inputs and window closing. If the event hook
 * setup fails, the function also returns 1. If both initialization steps
 * succeed, the function returns 0, indicating a successful start of the
 * Cub3D application.
 *
 * @param cub Pointer to the t_Cub3d structure containing program context
 * and data.
 * @return Returns 0 if the application boots successfully, or 1 if there's an
 * error.
 * */
int	boot(t_Cub3d *cub)
{
	if (graphics(cub))
		return (1);
	hook_events(cub);
	mlx_loop(cub->mlx_ptr);
	return (0);
}
