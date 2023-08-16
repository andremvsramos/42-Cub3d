/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:12:03 by andvieir          #+#    #+#             */
/*   Updated: 2023/08/16 11:04:49 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

/**
 * @brief Free allocated memory and resources within the main program context.
 *
 * This function is responsible for releasing allocated memory and resources
 * within the main program context represented by the `t_Cub3d` structure. It
 * closes the map file, frees memory allocated for filenames, texture paths,
 * and texture setup structures.
 * Additionally, it releases the memory allocated for the main map
 * configuration and the overall program context.
 *
 * Note: MiniLibX resource releases have been commented out, and
 * additional cleanup for other resources (e.g., image data and window)
 * might be required.
 *
 * @param cub Pointer to the t_Cub3d structure containing program context and data.
 */
void	free_main(t_Cub3d *cub)
{
	close(cub->map->fd);
	if (cub->map->filename)
		free(cub->map->filename);
	if (cub->map->tex->path_east)
		free(cub->map->tex->path_east);
	if (cub->map->tex->path_west)
		free(cub->map->tex->path_west);
	if (cub->map->tex->path_east)
		free(cub->map->tex->path_north);
	if (cub->map->tex->path_east)
		free(cub->map->tex->path_south);
	if (cub->map->tex)
		free(cub->map->tex);
	if (cub->map->player)
		free(cub->map->player);
	if (cub->map)
		free(cub->map);
	/* if (cub->mlx_ptr)
	{
		mlx_destroy_image(cub->mlx_ptr, cub->img->img_ptr);
		mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
		mlx_destroy_display(cub->mlx_ptr);
		free(cub->mlx_ptr);
	}
	if (cub->img->addr)
		free(cub->img->addr);
	if (cub->img->img_ptr)
		free(cub->img->img_ptr);
	if (cub->img)
		free(cub->img); */
}
