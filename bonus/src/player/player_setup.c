/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 10:11:27 by andvieir          #+#    #+#             */
/*   Updated: 2023/09/28 10:11:27 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d_bonus.h"

/**
 * @brief Set the player's direction and camera plane for North or South
 * orientation.
 *
 * The `set_ns_direction` function is responsible for configuring the player's
 * direction and the camera's plane based on the provided orientation `i`. When
 * `i` is equal to 1, it sets the player's direction to North (facing upward)
 * and the camera's plane to create a leftward field of view. When `i` is equal
 * to 2, it sets the player's direction to South (facing downward) and the
 * camera's plane to create a rightward field of view.
 *
 * @param c Pointer to the `t_CameraConfig` structure containing camera
 * configuration data.
 * @param p Pointer to the `t_PlayerConfig` structure containing player
 * configuration data.
 * @param i An integer representing the desired orientation (1 for North,
 * 2 for South).
 */
static void	set_ns_direction(t_CameraConfig *c, t_PlayerConfig *p, int i)
{
	if (i == 1)
	{
		p->dir_x = 0;
		p->dir_y = -1;
		c->plane_x = c->fov;
		c->plane_y = 0;
	}
	else if (i == 2)
	{
		p->dir_x = 0;
		p->dir_y = 1;
		c->plane_x = -c->fov;
		c->plane_y = 0;
	}
}

/**
 * @brief Set the player's direction and camera plane for West or East
 * orientation.
 *
 * The `set_we_direction` function is responsible for configuring the player's
 * direction and the camera's plane based on the provided orientation `i`. When
 * `i` is equal to 3, it sets the player's direction to West (facing left) and
 * the camera's plane to create an upward field of view. When `i` is equal to 4,
 * it sets the player's direction to East (facing right) and the camera's plane
 * to create a downward field of view.
 *
 * @param c Pointer to the `t_CameraConfig` structure containing camera
 * configuration data.
 * @param p Pointer to the `t_PlayerConfig` structure containing player
 * configuration data.
 * @param i An integer representing the desired orientation (3 for West,
 * 4 for East).
 */
static void	set_we_direction(t_CameraConfig *c, t_PlayerConfig *p, int i)
{
	if (i == 3)
	{
		p->dir_x = -1;
		p->dir_y = 0;
		c->plane_x = 0;
		c->plane_y = -c->fov;
	}
	else if (i == 4)
	{
		p->dir_x = 1;
		p->dir_y = 0;
		c->plane_x = 0;
		c->plane_y = c->fov;
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
 * @brief Update the player's position and direction.
 *
 * The `update_player` function is responsible for updating the player's
 * position and orientation based on the character representing the player
 * ('N', 'S', 'W', or 'E') within the game map. It sets the player's direction
 * and position accordingly, ensuring that the player is correctly placed and
 * facing the right way at the start of the game.
 *
 * @param cub Pointer to the Cub3D game configuration structure.
 * @param m Pointer to the MapConfig structure containing the game map data.
 * @param i The row index indicating the player's vertical position in the map.
 * @param j The column index indicating the player's horizontal position in the
 * map.
 */
static void	update_player(t_Cub3d *cub, t_MapConfig *m, int i, int j)
{
	if (m->matrix[i][j] == 'N')
		set_ns_direction(cub->cam, cub->player, 1);
	else if (m->matrix[i][j] == 'S')
		set_ns_direction(cub->cam, cub->player, 2);
	else if (m->matrix[i][j] == 'W')
		set_we_direction(cub->cam, cub->player, 3);
	else if (m->matrix[i][j] == 'E')
		set_we_direction(cub->cam, cub->player, 4);
	cub->player->pos_y = i;
	cub->player->pos_x = j;
}

/**
 * @brief Set the initial position and direction of the player.
 *
 * The `set_player_position` function searches the game map for a player
 * starting position indicated by the characters 'N', 'S', 'E', or 'W',
 * representing the cardinal directions (North, South, East, West). When a
 * valid starting position is found, it sets the player's initial position and
 * direction accordingly. This function ensures that the player is correctly
 * placed in the game world before starting gameplay.
 *
 * @param cub Pointer to the `t_Cub3d` structure containing program context
 * and data.
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
				update_player(cub, cub->map, i, j);
				return ;
			}
			j++;
		}
		i++;
	}
}
