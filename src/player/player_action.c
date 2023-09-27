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

#include "../../headers/cub3d.h"

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

void	shoot_gun(t_Cub3d *cub, t_PlayerConfig *p, int *counter)
{
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
