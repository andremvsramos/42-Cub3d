/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:03:12 by andvieir          #+#    #+#             */
/*   Updated: 2023/08/17 09:31:56 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

/**
 * @brief Calculate the number of lines and maximum line
 * length in the game map.
 *
 * This function reads through the map file to determine the number of lines and
 * calculates the maximum line length in the game map. It iterates over each
 * line, incrementing the line count and updating the maximum line length based
 * on the characters encountered, accounting for tab characters that contribute
 * 4 spaces. The calculated values are stored in the t_Cub3d structure to
 * provide context for map processing and rendering.
 *
 * @param cub Pointer to the t_Cub3d structure containing
 * program context and data.
 */
void	get_map_n_lines(t_Cub3d *cub, int i)
{
	char	*line;
	int		aux_len;

	cub->map->n_lines = 0;
	i = 0;
	aux_len = 0;
	//close(cub->map->temp_fd);
	cub->map->temp_fd = open(".map", O_RDONLY);
	line = get_next_line(cub->map->temp_fd);
	/* while (cub->map->n_lines < cub->map->skip_counter)
	{
		cub->map->n_lines++;
		free(line);
		line = get_next_line(cub->map->fd);
	} */
	while (line)
	{
		cub->map->n_lines++;
		aux_len = 0;
		//puts(ft_itoa(ft_strlen(line)));
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
		free(line);
		line = get_next_line(cub->map->temp_fd);
	}
	free(line);
	close(cub->map->temp_fd);
}

/**
 * @brief Check the validity of top and bottom boundaries in the game map.
 *
 * This function checks the validity of the top and bottom boundaries of the
 * game map. It examines the provided `line` and `index` to determine if the
 * boundary being checked is the top (index 0) or the bottom (index equal to
 * the total number of lines). The function ensures that the specified
 * boundary consists entirely of valid characters, which can include
 * walls ('1'), tabs('\t'), and spaces (' ').
 *
 * If the boundary is valid, the function returns 0. If the boundary contains
 * any invalid characters, the function returns 1, indicating an invalid map
 * boundary.
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

	if (index == 0 || index == cub->map->n_lines)
	{
		i = 0;
		while (line[i])
		{
			if (!ft_strchr("1\t\n ", line[i]))
				return (1);
			i++;
		}
	}
	return (0);
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
