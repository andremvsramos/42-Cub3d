/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:45:39 by andvieir          #+#    #+#             */
/*   Updated: 2023/10/02 10:41:05 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

/**
 * @brief Check the validity of floor and ceiling color settings in
 * the map information.
 *
 * This function validates the correctness of floor and ceiling color settings
 * within the scene description. It checks for valid color settings for the
 * floor and ceiling, ensuring that each color value is within the valid range.
 * If valid colors are found, the function stores the color settings in the
 * `colors` array of the `t_MapConfig` structure within the provided
 * `t_Cub3d` context.
 *
 * If the color settings are valid, the function returns 0.
 * If an invalid or duplicate color setting is encountered, the function
 * returns 1, indicating an error.
 *
 * @param cub Pointer to the t_Cub3d structure containing program
 * context and data.
 * @param line A pointer to the current line being processed from the map file.
 * @return Returns 0 if the color settings are valid, or 1 if an error occurs.
 */
int	has_valid_info3(t_Cub3d *cub, char *line)
{
	if (!ft_strncmp("F ", line, 2))
	{
		if (!cub->map->colors[0])
			put_floor_ceil_color(cub, line, 0, 0);
		else
			return (1);
	}
	else if (!ft_strncmp("C ", line, 2))
	{
		if (!cub->map->colors[1])
			put_floor_ceil_color(cub, line, 1, 0);
		else
			return (1);
	}
	return (0);
}

/**
 * @brief Check the validity of texture path settings for map elements.
 *
 * This function checks the correctness of texture path settings for specific
 * map elements within the scene description. It examines the provided `line`
 * to determine if it represents a valid texture path for the north (NO),
 * south (SO), west (WE), or east (EA) side of the map. If a valid texture
 * path is found, it invokes the `set_tex_path` function to store the path
 * in the appropriate member of the `t_MapConfig` structure within the
 * provided `t_Cub3d` context. If the texture path setting is invalid or a
 * duplicate, the function returns 1 to indicate an error.
 *
 * @param cub Pointer to the t_Cub3d structure containing program
 * context and data.
 * @param line A pointer to the current line being processed from the map file.
 * @return Returns 0 if the texture path setting is valid,
 * or 1 if an error occurs.
 */
int	set_tex_path(t_Cub3d *cub, char *path, int direction)
{
	char	*temp;

	temp = ft_strdup(path + 3);
	if (direction == 1 && !cub->map->tex_north->path)
		cub->map->tex_north->path = ft_strtrim(temp, " \t\n");
	else if (direction == 2 && !cub->map->tex_south->path)
		cub->map->tex_south->path = ft_strtrim(temp, " \t\n");
	else if (direction == 3 && !cub->map->tex_west->path)
		cub->map->tex_west->path = ft_strtrim(temp, " \t\n");
	else if (direction == 4 && !cub->map->tex_east->path)
		cub->map->tex_east->path = ft_strtrim(temp, " \t\n");
	else if (direction == 9 && !cub->map->tex_door->path)
		cub->map->tex_door->path = ft_strtrim(temp, " \t\n");
	else
		return (free(temp), 1);
	return (free (temp), 0);
}

/**
 * @brief Check and set additional information in the Cub3D configuration.
 *
 * The `has_valid_info2` function checks if the given line corresponds to any
 * additional information in the map file, such as bonus-related details. It
 * checks for valid information related to textures for the north, south, west,
 * east walls, and doors. If valid information is found, it calls appropriate
 * functions to set the corresponding texture paths in the `cub` configuration.
 *
 * @param cub Pointer to the main Cub3D configuration.
 * @param line The line from the map file being processed.
 * @return 1 if an error occurs (e.g., invalid path), 0 otherwise.
 */
int	has_valid_info2(t_Cub3d *cub, char *line)
{
	if (check_north_south(cub, line))
		return (1);
	else if (check_west_east(cub, line))
		return (1);
	else if (BONUS && !ft_strncmp("DO ", line, 3))
	{
		if (set_tex_path(cub, line, 9))
			return (1);
	}
	return (0);
}

/**
 * @brief Check and set map-related configuration in the Cub3D structure.
 *
 * The `has_valid_info` function is responsible for reading and processing map-
 * related configuration information from the map file. It handles the parsing
 * of texture paths for north, south, west, and east walls, as well as colors for
 * the ceiling and floor. Depending on whether the bonus features are enabled,
 * it may also check for additional bonus-related information. If any errors are
 * encountered during parsing (e.g., invalid paths), the function returns an
 * error code.
 *
 * @param cub Pointer to the main Cub3D configuration.
 * @return 1 if an error occurs during parsing, 0 otherwise.
 */
int	has_valid_info(t_Cub3d *cub, char *line)
{
	ft_open(cub);
	line = get_next_line(cub->map->fd);
	if (!BONUS)
	{
		while ((!cub->map->tex_north->path || !cub->map->tex_south->path
				|| !cub->map->tex_west->path || !cub->map->tex_east->path)
			|| (!cub->map->colors[0] || !cub->map->colors[1]))
		{
			if (ft_strchr("D1\t ", line[0]))
				return (ft_clean_gnl(cub->map->fd, line), 1);
			if (has_valid_info2(cub, line))
				return (ft_clean_gnl(cub->map->fd, line), 1);
			else if (has_valid_info3(cub, line))
				return (ft_clean_gnl(cub->map->fd, line), 1);
			free(line);
			line = get_next_line(cub->map->fd);
		}
		while (line)
			if (ft_strchr(line, 'D'))
				return (ft_clean_gnl(cub->map->fd, line), 1);
		ft_clean_gnl(cub->map->fd, line);
	}
	else if (fill_bonus_info(cub, line))
		return (1);
	return (0);
}
