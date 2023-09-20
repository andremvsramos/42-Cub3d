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
 * @brief Parse individual map elements and player orientation.
 *
 * This function is responsible for parsing individual characters in the
 * provided line from the map file. It checks whether the character is valid
 * and belongs to the set of allowed characters, including 0, 1, N, S, E, W,
 * newline, space, and tab. If the character represents a valid player
 * orientation (N, S, E, W), it invokes the set_player_orientation function to
 * handle setting the player's orientation. The function returns 1 if an invalid
 * character is encountered, or if there's an issue setting the player's
 * orientation. Otherwise, it returns 0.
 *
 * @param cub Pointer to the t_Cub3d structure containing program
 * context and data.
 * @param line A pointer to the current line being processed.
 * @param i The index of the character within the line.
 * @return Returns 1 if there's an error, or 0 if the character is valid.
 */
static int	parse_elements2(t_Cub3d *cub, char *line, int i)
{
	char	*charset;

	charset = "01NSEW\n\t ";
	if (BONUS)
		charset = "019NSEW\n\t ";
	if (!ft_strchr(charset, line[i]))
		return (1);
	else if (set_player_orientation(cub, line[i]))
		return (1);
	return (0);
}

/**
 * @brief Parse map elements and player orientation from the map file.
 *
 * This function parses individual characters in the map file, extracting and
 * validating each character as a valid map element. To streamline parsing and
 * avoid the need to repeatedly skip texture and color information at the
 * beginning of the file, the function first creates a temporary map file that
 * contains only the map layout. It then reads each line from the temporary
 * map file and processes each character using the parse_elements2 function. If
 * any character is invalid or if there's an issue setting the player's
 * orientation, the function returns an error. Otherwise, it returns 0.
 *
 * By making use of the temporary map file, this function ensures that the
 * parsing process maintains a connection with the original map file data. This
 * approach effectively eliminates the necessity of repeatedly skipping over
 * extraneous information. The temporary map file exclusively captures the map
 * layout, streamlining the parsing process and obviating the need for redundant
 * steps.
 *
 * @param cub Pointer to the t_Cub3d structure containing program context and
 * data.
 * @param i An integer used for iterating through characters in the line.
 * @return Returns 0 if the parsing is successful, or 1 if an error occurs.
 */
int	parse_elements(t_Cub3d *cub, int i)
{
	char	*line;

	ft_open(cub);
	line = get_next_line(cub->map->fd);
	if (!line)
		return (1);
	line = skip_info(cub, line);
	create_temp_map(cub, line);
	close(cub->map->temp_fd);
	cub->map->temp_fd = open("./.map", O_RDONLY);
	line = get_next_line(cub->map->temp_fd);
	if (!line)
		return (1);
	while (line)
	{
		i = 0;
		while (line[i++])
			if (parse_elements2(cub, line, i))
				return (free(line), 1);
		free(line);
		line = get_next_line(cub->map->temp_fd);
	}
	return (close(cub->map->temp_fd), free(line), 0);
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
	get_map_n_lines(cub);
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
		printf("Error: Invalid or missing texture/color info\n");
		exit(EXIT_FAILURE);
	}
	if (!cub->map->filename || is_valid_map_file(cub))
	{
		free_main(cub);
		printf("Error: Cannot read map file or is of wrong type\n");
		exit(EXIT_FAILURE);
	}
	if (check_map_validity(cub))
	{
		free_main(cub);
		printf("Error: Map is invalid or contains invalid elements\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}
