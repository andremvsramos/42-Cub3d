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

static void	set_player_direction(t_PlayerConfig *p, int i)
{
	if (i == 1)
	{
		p->dir_x = 0;
		p->dir_y = 1;
	}
	else if (i == 2)
	{
		p->dir_x = 0;
		p->dir_y = -1;
	}
	else if (i == 3)
	{
		p->dir_x = -1;
		p->dir_y = 0;
	}
	else if (i == 4)
	{
		p->dir_x = 1;
		p->dir_y = 0;
	}
}

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
	cub->player->orientation = 0;
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
		j = 0;
		while (cub->map->matrix[i][j])
		{
			if (ft_strchr("NSEW", cub->map->matrix[i][j]))
			{
				if (cub->map->matrix[i][j] == 'N')
					set_player_direction(cub->player, 1);
				else if (cub->map->matrix[i][j] == 'S')
					set_player_direction(cub->player, 2);
				else if (cub->map->matrix[i][j] == 'W')
					set_player_direction(cub->player, 3);
				else if (cub->map->matrix[i][j] == 'E')
					set_player_direction(cub->player, 4);
				cub->player->pos_y = i;
				cub->player->pos_x = j;
				return ;
			}
			j++;
		}
		i++;
	}
	cub->cam->plane_x = cub->player->dir_y * 0.66;  // Perpendicular to dir_x
	cub->cam->plane_y = -cub->player->dir_x * 0.66; // Perpendicular to dir_y
}
