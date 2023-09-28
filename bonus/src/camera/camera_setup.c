/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 10:10:12 by andvieir          #+#    #+#             */
/*   Updated: 2023/09/28 10:10:12 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d_bonus.h"

/**
 * @brief Initializes the camera configuration for raycasting.
 *
 * This function sets various fields in the camera configuration structure to
 * their initial values. It is typically called before performing raycasting
 * and collision detection to ensure that camera-related variables start with
 * proper values.
 *
 * @param cam Pointer to the t_CameraConfig structure to be initialized.
 */
void	cam_utils_init(t_CameraConfig *cam)
{
	cam->s_dist_x = 0;
	cam->s_dist_y = 0;
	cam->perp_wd = 0;
	cam->step_x = 0;
	cam->step_y = 0;
	cam->hit = 0;
	cam->side = 0;
	cam->line_height = 0;
	cam->draw_start = 0;
	cam->draw_end = 0;
}

/**
 * @brief Initializes the camera configuration.
 *
 * This function initializes the camera configuration structure, setting the
 * field of view (fov) to a default value and marking the camera as valid.
 *
 * @param cub Pointer to the main game structure (t_Cub3d).
 * @return Returns 0 on success, or 1 if memory allocation fails.
 */
int	camera_init(t_Cub3d *cub)
{
	cub->cam = ft_calloc(1, sizeof(t_CameraConfig));
	if (!cub->cam)
		return (1);
	cub->cam->fov = 1;
	cub->cam_ok = true;
	return (0);
}
