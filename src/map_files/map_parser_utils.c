/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:03:12 by andvieir          #+#    #+#             */
/*   Updated: 2023/09/20 15:47:30 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

/**
 * @brief Utility function to calculate the maximum line length and total lines
 * in the game map.
 *
 * The `get_map_n_lines_utils` function is a utility used during the map parsing
 * process to calculate the maximum line length and the total number of lines in
 * the game map. It iterates through the characters in a line, considering both
 * tabs and regular characters. Tabs are used for formatting the map, and their
 * count is used to ensure consistent formatting. For each character, the
 * function updates the auxiliary length and counts tabs. When a tab character
 * is encountered, it checks for the formatting rules. If a tab is part of a
 * series of tabs that exceeds the formatting rule, it contributes to the
 * auxiliary length, ensuring consistent spacing in the map. Finally, the
 * function updates the maximum line length in the map configuration structure
 * and increments the total line count.
 *
 * @param cub Pointer to the `t_Cub3d` structure containing program context and
 * data.
 * @param line A pointer to the input line containing map data.
 */
static	void	get_map_n_lines_utils(t_Cub3d *cub, char *line)
{
	int	aux_len;
	int	i;
	int	tabs;

	i = 0;
	aux_len = 0;
	tabs = 0;
	cub->map->n_lines++;
	while (line[i++])
	{
		tabs++;
		if (line[i] == '\t')
		{
			if (tabs == 8)
				tabs = 0;
			while (tabs++ <= 8)
				aux_len++;
			tabs = 0;
		}
		else
			aux_len++;
		if (tabs >= 7)
			tabs = 0;
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
	char	*charset;

	charset = "01\n\t ";
	if (BONUS)
		charset = "019\n\t ";
	if (ft_strchr("NSEW", c) && !cub->player->orientation)
		cub->player->orientation = c;
	else if (!ft_strchr(charset, c))
		return (1);
	return (0);
}
