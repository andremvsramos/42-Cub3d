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

#include "../headers/cub3d.h"

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
	len = ft_strlen(cub->filename) - 1;
	i = 4;
	while (i)
		if (cub->filename[len--] != filetype[--i])
			return (1);
	cub->fd = open(cub->filename, O_RDONLY);
	if (cub->fd < 0)
		return (1);
	return (0);
}

int	parse_elements(t_Cub3d *cub)
{
	char	*line;
	int		i;

	line = get_next_line(cub->fd);
	if (!line)
		return (free(line), 1);
	while (line)
	{
		i = 0;
		while (line[i])
			if (!ft_strchr("01NSEW\n\t", line[i++]))
				return (free(line), 1);
		free(line);
		line = get_next_line(cub->fd);
	}
	return (free(line), 0);
}

/* int	hasValidBoundaries(t_Cub3d *cub)
{
	char	**line;
	int		index;
	int		i;
	int		j;

	line = ft_calloc(1, sizeof(char *));
	*line = get_next_line(cub->fd);
	if (!*line)
		return (free(*line), free(line), 1);
	while (*line = get_next_line(cub->fd))
	{
		i = 0;
		while (*line[i])
		{
			j = 0;
			if (i = 0)
				if (!ft_strchr("1\t\n", *line[j++]))
					return (free(*line), free(line), 1);
			else
			{

			}
		}
		index++;
	}

} */

int	check_map_validity(t_Cub3d *cub)
{
	if (parse_elements(cub) /*|| has_valid_boundaries(cub)*/)
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
	if (!cub->filename || is_valid_map_file(cub))
	{
		close(cub->fd);
		free(cub->filename);
		shutdown("Error: Cannot read map file or is of wrong type\n", true);
	}
	if (check_map_validity(cub))
	{
		close(cub->fd);
		free(cub->filename);
		shutdown("Error: Map is invalid or contains invalid elements\n", true);
	}
	return (0);
	// TODO: Implement map file parsing and validation logic here.
}
