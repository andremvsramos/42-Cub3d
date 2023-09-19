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
