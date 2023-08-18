/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:20:46 by andvieir          #+#    #+#             */
/*   Updated: 2023/08/10 16:20:46 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

/**
 * @brief Check if the provided scene description file has a valid map type
 * for the Cub3D project.
 *
 * This function checks whether the provided scene description file,
 * represented by the `cub` context structure, has a valid map type indicated
 * by the ".cub" extension. It compares the characters in reverse order,
 * starting from the end of the file name, with the characters in the ".cub"
 * extension.
 *
 * Additionally, the function opens the file specified in the `cub` structure
 * using the `open` system call with read-only permissions. If the file cannot
 * be opened, the function returns 1 to indicate an error.
 *
 * @param cub Pointer to the t_Cub3d structure containing the scene description
 * and context data.
 * @return 1 if the file has a valid map type or cannot be opened, 0 if the
 * file is valid and opened successfully.
 */
int	is_valid_map_file(t_Cub3d *cub)
{
	char	*filetype;
	int		len;
	int		i;

	filetype = ".cub";
	len = ft_strlen(cub->map->filename) - 1;
	i = 4;
	while (i)
		if (cub->map->filename[len--] != filetype[--i])
			return (1);
	return (0);
}

/**
 * @brief Check the validity of the game map configuration and
 * set player orientation.
 *
 * This function performs various checks to validate the game map
 * configuration. It first retrieves the number of lines in the map and then
 * proceeds to parse the elements and boundaries of the map. For each valid
 * character encountered ('0', '1', 'N', 'S', 'E', 'W',
 * newline, tab, or space), it checks and sets the player's orientation
 * accordingly using the set_player_orientation function.
 * If any checks fail or an invalid character is encountered, indicating an
 * invalid map, the function returns 1.
 * Otherwise, if all checks pass, it returns 0.
 *
 * @param cub Pointer to the t_Cub3d structure containing program context
 * and data.
 * @param i Index used for iterating through each character in the map.
 * @return Returns 0 if the map configuration is valid and player
 * orientation is set, or 1 if any checks fail.
 */
int	parse_elements(t_Cub3d *cub, int i)
{
	char	*line;

	//close(cub->map->fd);
	ft_open(cub);
	line = get_next_line(cub->map->fd);
	if (!line)
		return (free(line), 1);
	line = skip_info(cub, line);
	//close(cub->map->fd);
	//close(cub->map->fd);
	create_temp_map(cub, line);
	close(cub->map->temp_fd);
	cub->map->temp_fd = open("./.map", O_RDONLY);
	line = get_next_line(cub->map->temp_fd);
	if (!line)
		return (free(line), 1);
	while (line)
	{
		i = 0;
		while (line[i])
		{
			if (!ft_strchr("01NSEW\n\t ", line[i]))
				return (free(line), 1);
			else if (set_player_orientation(cub, line[i]))
				return (free(line), 1);
			i++;
		}
		free(line);
		line = get_next_line(cub->map->temp_fd);
	}
	close(cub->map->temp_fd);
	return (free(line), 0);
}

/**
 * Checks the validity of the map within the Cub3d game structure.
 *
 * This function examines the provided Cub3d structure to determine whether the
 * map data it holds is valid. It involves parsing map elements, retrieving the
 * number of lines, and performing certain adjustments to the map data.
 *
 * @param cub - A pointer to a t_Cub3d structure containing game-related data.
 * @return 1 if the map is found to be invalid, 0 if the map is valid.
 */
int	check_map_validity(t_Cub3d *cub)
{
	if (parse_elements(cub, 0))
		return (1);
	get_map_n_lines(cub, 0);
	cub->map->n_lines--;
	return (0);
}

/**
 * @brief Parse and validate the scene description map file for the Cub3D
 * project.
 *
 * This function is responsible for parsing the provided scene description
 * map file. It reads and validates the map file's content, ensuring it
 * adheres to the specified rules, such as the correct map structure and
 * element order. It also validates that the file is of the correct
 * type (".cub" extension).
 *
 * If the map file is valid, the function should populate the appropriate
 * data structures within the `t_Cub3d` object passed as `cub`. If the file
 * is invalid or cannot be read, the function frees allocated memory,
 * terminates the program with an error message, and sets the `crash` flag
 * to true to indicate an error.
 *
 * @param cub Pointer to the t_Cub3d structure containing program
 * context and data.
 */
int	parse_map_file(t_Cub3d *cub)
{
	if (has_valid_info(cub))
	{
		free_main(cub);
		shutdown("Error: Invalid or missing texture/color info\n", true);
	}
	if (!cub->map->filename || is_valid_map_file(cub))
	{
		free_main(cub);
		shutdown("Error: Cannot read map file or is of wrong type\n", true);
	}
	if (check_map_validity(cub))
	{
		free_main(cub);
		shutdown("Error: Map is invalid or contains invalid elements\n", true);
	}
	return (printf("Success: Map has passed all validations\n"), 0);
	// TODO: Implement map file parsing and validation logic here.
}
