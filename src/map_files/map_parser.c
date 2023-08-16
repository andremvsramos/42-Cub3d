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
	ft_open(cub);
	return (0);
}

/**
 * @brief Check the validity of the game map configuration.
 *
 * This function performs various checks to validate the game map
 * configuration. It first retrieves the number of lines in the map and then
 * proceeds to parse the elements and boundaries of the map. If any of these
 * checks fail, indicating an invalid map, the function returns 1. Otherwise,
 * if all checks pass, it returns 0.
 *
 * @param cub Pointer to the t_Cub3d structure containing program context
 * and data.
 * @return Returns 0 if the map configuration is valid,
 * or 1 if any checks fail.
 */
int	parse_elements(t_Cub3d *cub, int i)
{
	char	*line;

	ft_open(cub);
	line = get_next_line(cub->map->fd);
	if (!line)
		return (free(line), 1);
	line = skip_info(cub, line);
	if (!line)
		return (free(line), 1);
	while (line)
	{
		while (line[i])
		{
			if (ft_strchr("01NSEW\n\t ", line[i]))
			{
				if (set_player_orientation(cub, line[i]))
					return (free(line), 1);
			}
			else
				return (free(line), 1);
			i++;
		}
		free(line);
		line = get_next_line(cub->map->fd);
	}
	return (free(line), 0);
}

/**
 * @brief Check the validity of the boundaries of the game map.
 *
 * This function checks the validity of the boundaries of the game map,
 * including the top, bottom, left, and right boundaries. It reads and validates
 * the map's top and bottom boundaries to ensure they consist entirely of walls
 * ('1'). Additionally, it checks the left and right boundaries of each row to
 * ensure they are also walls. This function ensures that the game map is
 * surrounded by walls on all sides as expected.
 *
 * If the boundaries are valid, the function returns 0. If any boundary check
 * fails, indicating an invalid map, the function frees allocated memory,
 * terminates the program with an error message, and sets the `crash` flag to
 * true to indicate an error.
 *
 * @param cub Pointer to the t_Cub3d structure containing
 * program context and data.
 * @return Returns 0 if the map boundaries are valid, or 1 if any
 * boundary check fails.
 */
int	has_valid_boundaries(t_Cub3d *cub)
{
	char	*line;
	int		index;

	ft_open(cub);
	line = get_next_line(cub->map->fd);
	if (!line)
		return (free(line), 1);
	index = 0;
	while (line)
	{
		if (check_bot_top_boundaries(cub, line, index))
			return (free(line), 1);
		free(line);
		line = get_next_line(cub->map->fd);
		index++;
	}
	return (free(line), 0);
}

/**
 * @brief Parse and validate the map elements of the scene description
 * for the Cub3D project.
 *
 * This function is responsible for parsing and validating the map elements
 * within the provided scene description. It reads and validates the map's
 * elements, ensuring they adhere to the specified rules. The function checks
 * that each character in the map is a valid map element ('0' for empty space,
 * '1' for walls, 'N', 'S', 'E', or 'W' for player orientations, and valid
 * separators like newline, tab, and space).
 *
 * If the map elements are valid, the function returns 0. If any map element
 * is invalid, the function frees allocated memory, terminates the program with
 * an error message, and sets the `crash` flag to true to indicate an error.
 *
 * @param cub Pointer to the t_Cub3d structure containing program
 * context and data.
 * @return Returns 0 if the map elements are valid, or terminates the
 * program with an error.
 */
int	check_map_validity(t_Cub3d *cub)
{
	get_map_n_lines(cub);
	cub->map->n_lines--;
	if (parse_elements(cub, 0) || has_valid_boundaries(cub))
		return (1);
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
 * @param cub Pointer to the t_Cub3d structure containing program context and data.
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
	close(cub->map->fd);
	if (check_map_validity(cub))
	{
		free_main(cub);
		shutdown("Error: Map is invalid or contains invalid elements\n", true);
	}
	return (ft_printf("Success: Map has passed all validations"), 0);
	// TODO: Implement map file parsing and validation logic here.
}
