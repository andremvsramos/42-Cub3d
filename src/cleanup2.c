/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: programming-pc <programming-pc@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:07:17 by andvieir          #+#    #+#             */
/*   Updated: 2023/09/27 15:31:42 by programming      ###   ########.fr       */
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
