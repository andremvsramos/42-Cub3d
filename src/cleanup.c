/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:12:03 by andvieir          #+#    #+#             */
/*   Updated: 2023/09/18 14:50:20 by andvieir         ###   ########.fr       */
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
	close(cub->map->fd);
	close(cub->map->temp_fd);
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
static void	free_textures(t_Cub3d *cub, t_TextureSetup *texture)
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
	if (cub->graphics_ok)
	{
		free_textures(cub, cub->map->tex_north);
		free_textures(cub, cub->map->tex_south);
		free_textures(cub, cub->map->tex_west);
		free_textures(cub, cub->map->tex_east);
		mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
		mlx_destroy_display(cub->mlx_ptr);
		free(cub->mlx_ptr);
	}
}

/**
 * @brief Free allocated memory and resources within the main program context.
 *
 * The `free_main` function is responsible for releasing allocated memory and
 * resources within the main program context represented by the `t_Cub3d`
 * structure. It closes the map file, frees memory allocated for filenames,
 * texture paths, and texture setup structures. Additionally, it releases the
 * memory allocated for the main map configuration, the player configuration,
 * and the overall program context.
 *
 * @param cub Pointer to the `t_Cub3d` structure containing program context
 * and data.
 */
void	free_main(t_Cub3d *cub)
{
	free_map(cub);
	free_graphics(cub);
	if (cub->map->matrix)
		free(cub->map->matrix);
	if (cub->map->filename)
		free(cub->map->filename);
	if (cub->player)
		free(cub->player);
	if (cub->map)
		free(cub->map);
}