/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:03:12 by andvieir          #+#    #+#             */
/*   Updated: 2023/08/15 18:44:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

/**
 * @brief Calculate the number of lines in the game map file.
 *
 * This function calculates and stores the number of lines present in the game
 * map file. It reads the map file line by line using the `get_next_line`
 * function and increments the line count for each successfully read line. The
 * final line count is stored in the `n_lines` member of the `t_MapConfig`
 * structure within the `t_Cub3d` context.
 *
 * @param cub Pointer to the t_Cub3d structure containing program
 * context and data.
 */
void	get_map_n_lines(t_Cub3d *cub)
{
	char	*line;

	cub->map->n_lines = 0;
	ft_open(cub);
	line = get_next_line(cub->map->fd);
	while (line)
	{
		cub->map->n_lines++;
		free(line);
		line = get_next_line(cub->map->fd);
	}
	free(line);
	close(cub->map->fd);
}

/**
 * @brief Check the validity of top and bottom boundaries in the game map.
 *
 * This function checks the validity of the top and bottom boundaries of the
 * game map. It examines the provided `line` and `index` to determine if the
 * boundary being checked is the top (index 0) or the bottom (index equal to
 * the total number of lines). The function ensures that the specified boundary
 * consists entirely of valid characters, which can include walls ('1'), tabs
 * ('\t'), and spaces (' ').
 *
 * If the boundary is valid, the function returns 0. If the boundary contains any
 * invalid characters, the function returns 1, indicating an invalid map boundary.
 *
 * @param cub Pointer to the t_Cub3d structure containing program context
 * and data.
 * @param line A pointer to the character array representing the
 * line being checked.
 * @param index The index of the current line within the map.
 * @return Returns 0 if the boundary is valid, or 1 if the boundary is invalid.
 */
int	check_bot_top_boundaries(t_Cub3d *cub, char *line, int index)
{
	int	i;

	if (index == cub->map->skip_counter || index == cub->map->n_lines)
	{
		i = 0;
		while (line[i])
		{
			if (ft_strchr("\n", line[i]))
				return (0);
			if (!ft_strchr("1\t ", line[i]))
				return (1);
			i++;
		}
	}
	return (0);
}
