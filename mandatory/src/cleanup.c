/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:12:03 by andvieir          #+#    #+#             */
/*   Updated: 2023/09/27 23:48:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

/**
 * @brief Free resources allocated for the map and close file descriptors.
 *
 * The `free_map` function is responsible for releasing memory and resources
 * associated with the map data in the Cub3D application. It first closes the
 * file descriptors for the map file and its temporary counterpart. Then, it
 * iterates through the matrix holding the map data and frees the memory for
 * each row.
 *
 * @param cub Pointer to the `t_Cub3d` structure containing program context and
 * data.
 */
static void	free_map(t_Cub3d *cub)
{
	int	i;

	i = 0;
	if (!cub->map->matrix)
		return ;
	while (i <= cub->map->n_lines)
	{
		if (cub->map->matrix[i])
			free(cub->map->matrix[i]);
		i++;
	}
}

/**
 * @brief Free allocated resources related to a texture setup in the Cub3D
 * application.
 *
 * The `free_textures` function is responsible for releasing allocated memory
 * and resources associated with a texture setup in the Cub3D application. It
 * takes a pointer to a `t_Cub3d` structure and a pointer to a `t_TextureSetup`
 * structure as arguments. The function first checks if the texture path is
 * allocated and frees it.
 * It then destroys the image created using `mlx_destroy_image` and releases
 * memory associated with the image's pixel data (`addr`). Subsequently, the
 * function frees memory associated with the image control structure itself.
 * Finally, the function frees the texture setup structure itself. If the
 * provided texture structure or its attributes are already `NULL`, the function
 * does not attempt to free them.
 *
 * @param cub Pointer to the `t_Cub3d` structure containing program context and
 * data.
 * @param texture Pointer to the `t_TextureSetup` structure representing the
 * texture to free.
 */
void	free_textures(t_Cub3d *cub, t_TextureSetup *texture)
{
	if (!texture)
		return ;
	if (texture->path)
		free(texture->path);
	if (texture->img)
	{
		if (texture->img->img_ptr)
			mlx_destroy_image(cub->mlx_ptr, texture->img->img_ptr);
		free(texture->img);
	}
	free(texture);
}

/**
 * @brief Free resources allocated for graphics and textures in the Cub3D
 * application.
 *
 * The `free_graphics` function is responsible for releasing memory and
 * resources associated with graphics and textures in the Cub3D application.
 * It checks if the `graphics_ok` flag is set to ensure that the graphics
 * context and textures were successfully initialized. If so, it proceeds to
 * free the textures for north, south, west, and east walls using the
 * `free_textures` function. After freeing the textures, it destroys the
 * application window using `mlx_destroy_window`, releases the display, and
 * frees the memory allocated for the MiniLibX context.
 *
 * @param cub Pointer to the `t_Cub3d` structure containing program context
 * and data.
 */
static void	free_graphics(t_Cub3d *cub)
{
	free_cam(cub);
	free_gun(cub);
	free_menu(cub);
	if (cub->graphics_ok)
	{
		if (cub->img)
		{
			if (cub->img->img_ptr)
				mlx_destroy_image(cub->mlx_ptr, cub->img->img_ptr);
			free(cub->img);
		}
		mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
		mlx_destroy_display(cub->mlx_ptr);
		free(cub->mlx_ptr);
	}
}

/**
 * @brief Deallocate resources associated with the minimap in the Cub3D game.
 *
 * The `free_minimap` function is responsible for freeing the memory resources
 * associated with the minimap in the Cub3D game. It first checks if the minimap
 * is initialized and active. If it is, the function proceeds to free the image
 * buffer used for the minimap and the minimap structure itself. This ensures
 * that memory is properly deallocated when it's no longer needed.
 *
 * @param cub Pointer to the Cub3D game configuration structure.
 */
static void	free_minimap(t_Cub3d *cub)
{
	if (cub->minimap_ok == false)
		return ;
	if (cub->minimap->img)
	{
		if (cub->minimap->img->img_ptr)
			mlx_destroy_image(cub->mlx_ptr, cub->minimap->img->img_ptr);
		free(cub->minimap->img);
	}
	free(cub->minimap);
}

/**
 * @brief Deallocate resources associated with the main game configuration.
 *
 * The `free_main` function is responsible for freeing memory and resources
 * associated with the main game configuration in the Cub3D game. It performs
 * the following actions:
 *
 * 1. Calls the `free_minimap` function to release resources related to the
 * minimap.
 * 2. Calls the `free_graphics` function to release graphics-related resources.
 * 3. Calls the `free_map` function to deallocate memory related to the game
 * map.
 * 4. Checks if the camera structure (`cub->cam`) is initialized (`cam_ok` flag)
 *    and frees it if necessary.
 * 5. Checks if the matrix representing the game map (`cub->map->matrix`) is
 *    initialized and frees it if necessary.
 * 6. Checks if the filename associated with the map (`cub->map->filename`) is
 *    initialized and frees it if necessary.
 * 7. Checks if the player configuration structure (`cub->player`) is initialized
 *    and frees it if necessary.
 * 8. Finally, frees the memory associated with the game map structure
 * (`cub->map`).
 *
 * @param cub Pointer to the main Cub3D game configuration structure.
 */
void	free_main(t_Cub3d *cub)
{
	free_minimap(cub);
	free_graphics(cub);
	free_map(cub);
	if (cub->cam_ok)
		free(cub->cam);
	if (cub->map->matrix)
		free(cub->map->matrix);
	if (cub->map->filename)
		free(cub->map->filename);
	if (cub->player)
		free(cub->player);
	if (cub->map)
		free(cub->map);
}
