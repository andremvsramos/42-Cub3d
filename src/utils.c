/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:12:03 by andvieir          #+#    #+#             */
/*   Updated: 2023/08/14 17:13:44 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

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
