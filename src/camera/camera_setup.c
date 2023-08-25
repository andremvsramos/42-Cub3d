/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 21:41:06 by marvin            #+#    #+#             */
/*   Updated: 2023/08/25 21:41:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

/**
 * @brief Initialize the camera configuration.
 *
 * The camera_init function allocates memory for the t_CameraConfig structure
 * that holds the camera's configuration parameters. It initializes the
 * structure with zero values using the calloc function and assigns it to the
 * 'cam' field of the t_Cub3d structure. If the memory allocation fails, the
 * function returns 1, indicating an error. Otherwise, it returns 0 to indicate
 * a successful initialization.
 *
 * @param cub Pointer to the t_Cub3d structure containing program context
 * and data.
 * @return Returns 0 if the camera configuration is successfully initialized,
 * or 1 if there's an error.
 */
int	camera_init(t_Cub3d *cub)
{
	cub->cam = ft_calloc(1, sizeof(t_CameraConfig));
	if (!cub->cam)
		return (1);
	return (0);
}

/**
 * @brief Initialize ray direction based on player's direction and field of
 * view.
 *
 * The raycast_init function calculates the initial ray direction for the camera.
 * It adds the player's direction components (dir_x and dir_y) to the
 * corresponding field of view components (fov_x and fov_y) and assigns the
 * results to the ray's direction components (raydir_x and raydir_y) in the
 * camera configuration. This initial ray direction will be used as the starting
 * point for raycasting in the game loop.
 *
 * @param cub Pointer to the t_Cub3d structure containing program context
 * and data.
 */
void	raycast_init(t_Cub3d *cub)
{
	cub->cam->raydir_x = cub->player->dir_x + cub->player->fov_x;
	cub->cam->raydir_y = cub->player->dir_y + cub->player->fov_y; // This one is if we want to include complex vertical camera movement, jumping, etc...
}
