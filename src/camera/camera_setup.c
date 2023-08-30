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

void	cam_utils_init(t_CameraConfig *cam, t_PlayerConfig *p)
{
	cam->s_dist_x = 0;
	cam->s_dist_y = 0;
	cam->perp_wd = 0;
	cam->step_x = 0;
	cam->step_y = 0;
	cam->hit = 0;
	cam->side = 0;
	cam->i_ray_x = p->pos_x;
	cam->i_ray_y = p->pos_y;
	cam->line_height = 0;
    cam->draw_start = 0;
    cam->draw_end = 0;
}

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
