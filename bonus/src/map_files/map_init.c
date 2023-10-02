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

#include "../../headers/cub3d_bonus.h"

/**
 * @brief Initialize texture configurations for the game map.
 *
 * The `tex_init` function is responsible for initializing texture
 * configurations for various directions (north, south, west, and east) in the
 * game map. These textures are essential for rendering the game environment.
 * Additionally, if the bonus features are enabled, it also initializes a door
 * texture.
 *
 * If any allocation failure occurs during the initialization process, the
 * function will free previously allocated memory, display an error message, and
 * terminate the program.
 *
 * @param cub Pointer to the main game structure.
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
		printf("Error: fatal: t_TextureSetup not created\n");
		exit(EXIT_FAILURE);
	}
	if (BONUS)
	{
		cub->map->tex_door = ft_calloc(1, sizeof(t_TextureSetup));
		if (!cub->map->tex_door)
		{
			free_main(cub);
			printf("Error: fatal: tex_door not created\n");
			exit(EXIT_FAILURE);
		}
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
		printf("Error: fatal: t_MapConfig not created\n");
		exit(EXIT_FAILURE);
	}
	cub->map->skip_counter = 0;
	cub->map->max_line_len = 0;
	cub->map->filename = ft_strdup(file);
	tex_init(cub);
	if (player_init(cub))
	{
		free_main(cub);
		printf("Error: Failed initializing player settings\n");
		exit(EXIT_FAILURE);
	}
	parse_map_file(cub);
	if (fill_matrix(cub))
		return (printf("Error: failed creating matrix\n"), 1);
	if (check_map_closed(cub))
		return (printf("Error: map isn't closed off\n"), 1);
	return (0);
}
