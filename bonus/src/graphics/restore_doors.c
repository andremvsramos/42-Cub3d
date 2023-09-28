/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_doors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:59:00 by andvieir          #+#    #+#             */
/*   Updated: 2023/09/28 10:08:14 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d_bonus.h"

/**
 * @brief Checks if a door tile placement in the map is valid.
 *
 * The `check_walls_doors` function examines the map configuration to determine
 * whether a door tile ('9') is correctly placed. In bonus mode, door tiles must
 * have specific surroundings to be considered valid: either walls to the west
 * (W) and east (E) with walkable paths to the north (N) and south (S), or walls
 * to the north (N) and south (S) with walkable paths to the west (W) and east
 * (E). If neither of these conditions is met, the function returns 1,
 * indicating an invalid door placement; otherwise, it returns 0, signifying a
 * valid door placement.
 *
 * @param m Pointer to the t_MapConfig structure containing map data.
 * @param i The row index of the door tile.
 * @param j The column index of the door tile.
 * @return 0 if the door tile placement is valid, 1 if it is invalid.
 */
int	check_walls_doors(t_MapConfig *m, int i, int j)
{
	if (m->matrix[i][j] == '9')
	{
		if (BONUS)
		{
			if (m->matrix[i][j - 1] == '0' && m->matrix[i][j + 1] == '0' &&
				m->matrix[i - 1][j] == '1' && m->matrix[i + 1][j] == '1')
				return (0);
			else if (m->matrix[i][j - 1] == '1' && m->matrix[i][j + 1] == '1' &&
				m->matrix[i - 1][j] == '0' && m->matrix[i + 1][j] == '0')
				return (0);
			else
				return (1);
		}
		else
			return (1);
	}
	return (0);
}

/**
 * @brief Restores door tiles on the map if specific conditions are met.
 *
 * The `restore_doors` function scans the map for door tiles ('9') and restores
 * them to their original state under certain conditions. A door can be restored
 * if it has been previously opened ('0') and the player character is not in
 * proximity. The function reads the map data from a temporary file and checks
 * each door tile for restoration eligibility.
 *
 * @param cub Pointer to the t_Cub3d structure, representing the game context.
 * @param x The initial x-coordinate for scanning the map.
 * @param y The initial y-coordinate for scanning the map.
 */
void	restore_doors(t_Cub3d *cub, int x, int y)
{
	char	*line;

	cub->map->temp_fd = open("./.map", O_RDONLY);
	line = get_next_line(cub->map->temp_fd);
	if (!line)
		return ;
	while (line)
	{
		x = 0;
		while (line[x])
		{
			if (line[x] == '9')
			{
				if (cub->map->matrix[y][x] == '0'
					&& (cub->player->pos_y > y + 3 || cub->player->pos_y < y - 3
						|| cub->player->pos_x > x + 3
						|| cub->player->pos_x < x - 3))
					cub->map->matrix[y][x] = '9';
			}
			x++;
		}
		y++;
		free(line);
		line = get_next_line(cub->map->temp_fd);
	}
}
