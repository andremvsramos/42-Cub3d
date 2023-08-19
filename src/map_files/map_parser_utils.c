/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:03:12 by andvieir          #+#    #+#             */
/*   Updated: 2023/08/19 18:42:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

/**
 * @brief Helper function to calculate maximum line length and update number of
 * lines.
 *
 * This function is called by the get_map_n_lines function for each line read
 * from the map file. It calculates the length of the line, considering tabs
 * as four spaces, and updates the n_lines member of the cub->map data
 * structure. Additionally, it compares the calculated line length to the
 * current max_line_len value and updates it if the calculated length is larger.
 *
 * @param cub Pointer to the t_Cub3d structure containing program
 * context and data.
 * @param line A pointer to the current line being processed.
 */
static	void	get_map_n_lines_utils(t_Cub3d *cub, char *line)
{
	int	aux_len;
	int	i;

	i = 0;
	aux_len = 0;
	cub->map->n_lines++;
	aux_len = 0;
	i = 0;
	while (line[i])
	{
		if (ft_strchr("\t", line[i]))
			aux_len += 4;
		else
			aux_len++;
		i++;
	}
	if (aux_len > cub->map->max_line_len)
		cub->map->max_line_len = aux_len;
}

/**
 * @brief Calculate the number of lines in the map file.
 *
 * This function opens the map file and iterates through its lines using
 * the get_next_line function. For each non-empty line, it increments the
 * n_lines member in the cub->map data structure. After processing all lines,
 * the function closes the file descriptor and frees allocated resources.
 *
 * @param cub Pointer to the t_Cub3d structure containing program
 * context and data.
 */
void	get_map_n_lines(t_Cub3d *cub)
{
	char	*line;

	cub->map->n_lines = 0;
	cub->map->temp_fd = open(".map", O_RDONLY);
	line = get_next_line(cub->map->temp_fd);
	while (line)
	{
		get_map_n_lines_utils(cub, line);
		free(line);
		line = get_next_line(cub->map->temp_fd);
	}
	free(line);
	close(cub->map->temp_fd);
}

/**
 * @brief Set the player's orientation based on a valid map element.
 *
 * This function is responsible for setting the player's orientation based on
 * a valid map element character ('N', 'S', 'E', 'W'). It checks if the provided
 * character represents a valid orientation and if the player's orientation has
 * not been set already. If the conditions are met, the player's orientation is
 * updated in the t_Cub3d structure. If the character is not a valid orientation
 * or the orientation has already been set, the function returns an error code.
 *
 * @param cub Pointer to the t_Cub3d structure containing program context
 * and data.
 * @param c The character representing the map element.
 * @return Returns 0 if the player's orientation is successfully set,
 * or 1 if the character is not a valid orientation or the orientation is
 * already set.
 */
int	set_player_orientation(t_Cub3d *cub, char c)
{
	if (ft_strchr("NSEW", c) && !cub->map->player->orientation)
		cub->map->player->orientation = c;
	else if (!ft_strchr("01\n\t ", c))
		return (1);
	return (0);
}
