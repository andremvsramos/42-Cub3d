/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_doors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:59:00 by andvieir          #+#    #+#             */
/*   Updated: 2023/09/28 17:28:21 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

/**
 * @brief Restore a door in the map matrix.
 *
 * The `restore` function checks if the specified position in the map matrix
 * contains a '0' and if the player's position is sufficiently far from it.
 * If these conditions are met, it changes the map value to '9', effectively
 * restoring that position.
 *
 * @param cub Pointer to the main Cub3D game configuration structure.
 * @param x The x-coordinate in the map matrix.
 * @param y The y-coordinate in the map matrix.
 */
static void	restore(t_Cub3d *cub, int x, int y)
{
	if (cub->map->matrix[y][x] == '0'
		&& (cub->player->pos_y > y + 3 || cub->player->pos_y < y - 3
			|| cub->player->pos_x > x + 3
			|| cub->player->pos_x < x - 3))
		cub->map->matrix[y][x] = '9';
}

/**
 * @brief Count tabs in a line and calculate the horizontal position.
 *
 * The `count_tabs` function counts the number of tabs in a line and calculates
 * the horizontal position (x) based on the tab count. It also resets the tab
 * count to 0 after processing tabs. This function is typically used to track
 * horizontal positions in a line containing tabs.
 *
 * @param line A string representing a line of text.
 * @param i The current index within the line.
 * @param tabs A pointer to an integer storing the tab count.
 * @return The horizontal position (x) calculated based on tab count.
 */
static int	count_tabs(char *line, int i, int *tabs)
{
	int	x;

	x = 0;
	(*tabs)++;
	if (line[i] == '\t')
	{
		if (*tabs == 7)
			(*tabs) = 0;
		while (*tabs < 8)
		{
			x++;
			(*tabs)++;
		}
		*tabs = 0;
	}
	else if (*tabs == 7)
		(*tabs) = 0;
	return (x);
}

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
			if ((m->matrix[i][j - 1] == '0'
				|| ft_strchr("NSEW", m->matrix[i][j - 1]))
				&& (m->matrix[i][j + 1] == '0'
				|| ft_strchr("NSEW", m->matrix[i][j + 1]))
				&& m->matrix[i - 1][j] == '1' && m->matrix[i + 1][j] == '1')
				return (0);
			else if (m->matrix[i][j - 1] == '1' && m->matrix[i][j + 1] == '1'
				&& (m->matrix[i - 1][j] == '0'
				|| ft_strchr("NSEW", m->matrix[i - 1][j]))
				&& (m->matrix[i + 1][j] == '0'
				|| ft_strchr("NSEW", m->matrix[i + 1][j])))
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
void	restore_doors(t_Cub3d *cub, int x, int y, int i)
{
	char	*line;
	int		tabs;

	tabs = 0;
	cub->map->temp_fd = open("./.map", O_RDONLY);
	line = get_next_line(cub->map->temp_fd);
	if (!line)
		return ;
	while (line)
	{
		x = 0;
		i = 0;
		tabs = 0;
		while (line[i])
		{
			x += count_tabs(line, i, &tabs);
			if (line[i] == '9')
				restore(cub, x, y);
			x++;
			i++;
		}
		y++;
		free(line);
		line = get_next_line(cub->map->temp_fd);
	}
}
