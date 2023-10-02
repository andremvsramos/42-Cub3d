/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Untitled-1                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:20:00 by marvin            #+#    #+#             */
/*   Updated: 2023/09/19 12:20:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d_bonus.h"

/**
 * @brief Execute a use action in the game.
 *
 * The `use_action` function calculates the position where the player intends
 * to perform a use action based on their current position and direction. It
 * checks if the tile at the calculated position in the game map is a '9',
 * representing a door. If so, it changes the tile to '0', indicating that the
 * door has been used. Otherwise, it returns an error to signify that no
 * action was performed.
 *
 * @param p Pointer to the PlayerConfig structure containing player information.
 * @param m Pointer to the MapConfig structure containing game map information.
 * @return 0 if the use action was successful, 1 if no action was performed.
 */
int	use_action(t_PlayerConfig *p, t_MapConfig *m)
{
	p->use_distance_x = p->pos_x + 0.7 * p->dir_x;
	p->use_distance_y = p->pos_y + 0.7 * p->dir_y;
	if (m->matrix[(int)p->use_distance_y][(int)p->use_distance_x] == '9')
		m->matrix[(int)p->use_distance_y][(int)p->use_distance_x] = '0';
	else
		return (1);
	return (0);
}

/**
 * @brief Animate shooting the player's gun.
 *
 * The `shoot_gun` function manages the animation of shooting the player's gun.
 * It takes a counter as input to determine the current animation frame.
 * Depending on the counter's value, it updates the gun's image to display the
 * corresponding frame of the shooting animation. When the animation is
 * complete, it resets the counter and restores the gun's default image.
 *
 * @param cub Pointer to the Cub3D game configuration structure.
 * @param p Pointer to the PlayerConfig structure containing player information.
 * @param counter Pointer to an integer counter for animation frames.
 */
void	shoot_gun(t_Cub3d *cub, t_PlayerConfig *p, int *counter)
{
	if (*counter)
		mlx_destroy_image(cub->mlx_ptr, p->gun->img->img_ptr);
	if (*counter == 1)
		setup_menu(cub, p->gun, "./sprites/Gun_Sprites/g_01.xpm");
	else if (*counter == 2)
		setup_menu(cub, p->gun, "./sprites/Gun_Sprites/g_02.xpm");
	else if (*counter == 3)
		setup_menu(cub, p->gun, "./sprites/Gun_Sprites/g_03.xpm");
	else if (*counter == 4)
		setup_menu(cub, p->gun, "./sprites/Gun_Sprites/g_04.xpm");
	else if (*counter == 5)
	{
		setup_menu(cub, p->gun, "./sprites/Gun_Sprites/g_00.xpm");
		p->shoot = 0;
		*counter = 0;
	}
}
