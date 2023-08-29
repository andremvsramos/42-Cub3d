/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 19:40:50 by marvin            #+#    #+#             */
/*   Updated: 2023/08/25 19:40:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

/**
 * @brief Initialize the player configuration in the map.
 *
 * The `player_init` function is responsible for initializing the player's
 * configuration within the map. It allocates memory for a `t_PlayerConfig`
 * structure and sets the player's initial position to (-1, -1) within the
 * provided `t_Cub3d` context. Additionally, the player's field of view (FOV)
 * is set to a default horizontal FOV angle and a fixed vertical FOV angle.
 * The function then calls the `set_player_position` and `raycast_init`
 * functions to further configure the player's position and raycasting
 * initialization. If memory allocation fails, the function returns 1,
 * indicating failure.
 *
 * @param cub Pointer to the t_Cub3d structure containing program context and
 * data.
 * @return Returns 0 on success, or 1 on memory allocation failure.
 */
int	player_init(t_Cub3d *cub)
{
	cub->player = ft_calloc(1, sizeof(t_PlayerConfig));
	if (!cub->player)
		return (1);
	cub->player->pos_x = -1;
	cub->player->pos_y = -1;
	cub->player->fov_x = 0;
	cub->player->fov_y = 0.66;
	set_player_position(cub);
	raycast_init(cub);
	return (0);
}

/**
 * @brief Set the player's initial position based on the map.
 *
 * This function iterates through the map's matrix and sets the player's
 * position based on the occurrence of a valid player character
 * ('N', 'S', 'E', 'W').
 *
 * @param cub Pointer to the t_Cub3d structure containing program
 * context and data.
 */
void	set_player_position(t_Cub3d *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->map->matrix[i])
	{
		while (cub->map->matrix[i][j])
		{
			if (ft_strchr("NSEW", cub->map->matrix[i][j]))
			{
				cub->player->pos_y = i;
				cub->player->pos_x = j;
				return ;
			}
			j++;
		}
		i++;
	}
}
