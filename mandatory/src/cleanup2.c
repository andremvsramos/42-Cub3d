/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:07:17 by andvieir          #+#    #+#             */
/*   Updated: 2023/09/27 17:35:21 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	free_menu(t_Cub3d *cub)
{
	if (cub->menu_ok)
	{
		if (cub->main->start)
			free_textures(cub, cub->main->start);
		if (cub->main->quit)
			free_textures(cub, cub->main->quit);
		free(cub->main);
	}
	cub->menu_active = false;
}

void	free_gun(t_Cub3d *cub)
{
	if (cub->gun_ok)
	{
		if (cub->player->gun)
			free_textures(cub, cub->player->gun);
		if (cub->player->crosshair)
			free_textures(cub, cub->player->crosshair);
	}
}

void	free_cam(t_Cub3d *cub)
{
	int	i;

	i = 0;
	if (cub->map->tex_north)
		free_textures(cub, cub->map->tex_north);
	if (cub->map->tex_south)
		free_textures(cub, cub->map->tex_south);
	if (cub->map->tex_west)
		free_textures(cub, cub->map->tex_west);
	if (cub->map->tex_east)
		free_textures(cub, cub->map->tex_east);
	if (BONUS && cub->map->tex_door)
		free_textures(cub, cub->map->tex_door);
	if (cub->files_ok)
	{
		while (i < 4 + BONUS)
		{
			if (cub->cam->tex[i])
				free(cub->cam->tex[i]);
			i++;
		}
		free(cub->cam->tex);
	}
}
