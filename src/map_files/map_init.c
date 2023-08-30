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
 * It allocates memory for t_TextureSetup structures and initializes
 * their members. If memory allocation fails, the function calls free_main to
 * clean up allocated resources, terminates the program,
 * and displays an error message.
 *
 * @param cub Pointer to the t_Cub3d structure containing
 * program context and data.
 */
static void	tex_init(t_Cub3d *cub)
{
	cub->map->tex_north = ft_calloc(1, sizeof(t_TextureSetup));
	cub->map->tex_south = ft_calloc(1, sizeof(t_TextureSetup));
	cub->map->tex_west = ft_calloc(1, sizeof(t_TextureSetup));
	cub->map->tex_east = ft_calloc(1, sizeof(t_TextureSetup));
	if (!cub->map->tex_north || !cub->map->tex_south
		|| !cub->map->tex_west || !cub->map->tex_east)
	{
		free_main(cub);
		shutdown("Error: fatal: t_TextureSetup not created\n", true);
	}
	cub->map->colors[0] = false;
	cub->map->colors[1] = false;
}

/**
 * @brief Initialize map configuration and data within the Cub3D context.
 *
 * This function initializes the map configuration and data within the
 * Cub3D context. It allocates memory for a `t_MapConfig` structure and
 * initializes its members. The function sets the skip counter to 0 and
 * duplicates the provided filename. If memory allocation fails, the function
 * calls `free_main` to clean up allocated resources and terminates the program
 * with an error message.
 *
 * The function then initializes texture configuration using the `tex_init`
 * function. It proceeds to parse the map file using the `parse_map_file`
 * function and fill the map matrix using the `fill_matrix` function. Finally,
 * it checks if the map is properly enclosed by walls and has valid player
 * movement areas using the `check_map_closed` function. If any step encounters
 * an error, the function returns 1; otherwise, it returns 0 to indicate
 * successful initialization.
 *
 * @param cub Pointer to the `t_Cub3d` structure containing program context
 * and data.
 * @param file Name of the map file to be parsed.
 * @return Returns 1 if any initialization step fails, else returns 0.
 */
int	map_init(t_Cub3d *cub, char *file)
{
	cub->map = ft_calloc(1, sizeof(t_MapConfig));
	if (!cub->map)
	{
		free_main(cub);
		shutdown("Error: fatal: t_MapConfig not created\n", true);
	}
	cub->map->skip_counter = 0;
	cub->map->max_line_len = 0;
	cub->map->filename = ft_strdup(file);
	tex_init(cub);
	if (player_init(cub))
	{
		free_main(cub);
		shutdown("Error: Failed initializing player settings\n", true);
	}
	parse_map_file(cub);
	if (fill_matrix(cub))
		return (1);
	if (check_map_closed(cub))
		return (1);
	return (0);
}
