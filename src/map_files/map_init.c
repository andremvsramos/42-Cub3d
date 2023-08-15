/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:50:05 by marvin            #+#    #+#             */
/*   Updated: 2023/08/15 18:50:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

/**
 * @brief Initialize texture setup data within the Cub3D context.
 *
 * This function initializes the texture setup data within the Cub3D context.
 * It allocates memory for a t_TextureSetup structure and initializes
 * its members. If memory allocation fails, the function calls free_main to
 * clean up allocated resources and terminates the program
 * with an error message.
 *
 * @param cub Pointer to the t_Cub3d structure containing
 * program context and data.
 */
static void	tex_init(t_Cub3d *cub)
{
	cub->map->tex = ft_calloc(1, sizeof(t_TextureSetup));
	if (!cub->map->tex)
	{
		free_main(cub);
		shutdown("Error: fatal: t_TextureSetup not created\n", true);
	}
	cub->map->tex->colors[0] = false;
	cub->map->tex->colors[1] = false;
}

/**
 * @brief Initialize map configuration data within the Cub3D context.
 *
 * This function initializes the map configuration data within the
 * Cub3D context. It allocates memory for a t_MapConfig structure and
 * initializes its members. The function sets the skip counter to 0 and
 * duplicates the provided filename. If memory allocation fails, the function
 * calls free_main to clean up allocated resources and terminates the program
 * with an error message.
 *
 * @param cub Pointer to the t_Cub3d structure containing
 * program context and data.
 * @param av Array of command-line arguments, where av[1] is the filename.
 */
void	map_init(t_Cub3d *cub, char *file)
{
	cub->map = ft_calloc(1, sizeof(t_MapConfig));
	if (!cub->map)
	{
		free_main(cub);
		shutdown("Error: fatal: t_MapConfig not created\n", true);
	}
	cub->map->skip_counter = 0;
	cub->map->filename = ft_strdup(file);
	tex_init(cub);
	//cub.img = ft_calloc(1, sizeof(t_ImageControl));
}
