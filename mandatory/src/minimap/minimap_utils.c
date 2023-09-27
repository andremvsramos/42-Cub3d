/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 22:51:12 by marvin            #+#    #+#             */
/*   Updated: 2023/09/27 23:36:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

/**
 * @brief Find the maximum row length (number of columns) in the map matrix.
 *
 * The `max_x_array` function iterates through the rows of the map matrix and
 * calculates the length (number of columns) of each row. It keeps track of the
 * maximum row length encountered during the iteration, providing the maximum
 * width of the map grid.
 *
 * @param cub Pointer to the Cub3D game configuration structure.
 * @return The maximum row length (number of columns) in the map matrix.
 */
int	max_x_array(t_Cub3d *cub)
{
	int	y;
	int	x;
	int	most_x;

	y = 0;
	x = 0;
	most_x = 0;
	while (y < cub->map->n_lines + 1)
	{
		x = 0;
		while (cub->map->matrix[y][x])
			x++;
		if (x > most_x)
			most_x = x;
		y++;
	}
	return (most_x);
}
