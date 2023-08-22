/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:45:39 by andvieir          #+#    #+#             */
/*   Updated: 2023/08/22 11:12:33 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

static	void	put_floor_ceil_color_utils(t_Cub3d *cub, int n, char **colors)
{
	if (n == 0)
	{
		cub->map->tex->floor_c[ft_atoi(colors[0])]
		[ft_atoi(colors[1])]
		[ft_atoi(colors[2])] = 1;
	}
	else
	{
		cub->map->tex->ceilling_c[ft_atoi(colors[0])]
		[ft_atoi(colors[1])]
		[ft_atoi(colors[2])] = 1;
	}
}

/**
 * @brief Set and store floor or ceiling color settings in the map information.
 *
 * This function processes and stores floor or ceiling color settings within
 * the scene description. It extracts and converts the RGB color components
 * from the provided `line`, which represents a color setting, and sets the
 * corresponding entry in the `floor_c` or `ceiling_c` array of the
 * `t_TextureSetup` structure within the provided `t_Cub3d` context.
 * Additionally, the function performs validation on the provided color
 * components to ensure they are within the valid range of 0 to 255.
 * If any component is found to be out of range, the function terminates the
 * program with an error message.
 *
 * @param cub Pointer to the t_Cub3d structure containing
 * program context and data.
 * @param line A pointer to the current line containing the color setting.
 * @param n An integer indicating whether to process floor (0)
 * or ceiling (1) color.
 * @param i Index for iterating over the color components.
 */
void	put_floor_ceil_color(t_Cub3d *cub, char *line, int n, int i)
{
	char	**colors;

	colors = ft_split(line + 2, ',');
	while (i < 3)
	{
		if (!(ft_atoi(colors[i]) >= 0 && ft_atoi(colors[i]) <= 255))
		{
			free_main(cub);
			shutdown("Error: Invalid color range\n", true);
		}
		i++;
	}
	if (n == 0)
		put_floor_ceil_color_utils(cub, 0, colors);
	else
		put_floor_ceil_color_utils(cub, 1, colors);
	ft_free_split(colors);
	cub->map->tex->colors[n] = true;
}

/**
 * @brief Check the validity of floor and ceiling color settings in
 * the map information.
 *
 * This function validates the correctness of floor and ceiling color settings
 * within the scene description. It checks for valid color settings for the
 * floor and ceiling, ensuring that each color value is within the valid range.
 * If valid colors are found, the function stores the color settings in the
 * `colors` array of the `t_TextureSetup` structure within the provided
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
static int	has_valid_info3(t_Cub3d *cub, char *line)
{
	if (!ft_strncmp("F ", line, 2))
	{
		if (!cub->map->tex->colors[0])
			put_floor_ceil_color(cub, line, 0, 0);
		else
			return (1);
	}
	else if (!ft_strncmp("C ", line, 2))
	{
		if (!cub->map->tex->colors[1])
			put_floor_ceil_color(cub, line, 1, 0);
		else
			return (1);
	}
	return (0);
}

/**
 * @brief Set and store texture path settings in the map information.
 *
 * This function processes and stores texture path settings for specific map
 * elements within the scene description. It takes the provided `path` and
 * extracts the relevant part of the string after the direction identifier
 * (e.g., "NO ", "SO ", "WE ", "EA "). It then trims any leading whitespace
 * characters and assigns the trimmed path to the appropriate member of the
 * `t_TextureSetup` structure within the provided `t_Cub3d` context. The
 * `direction` parameter determines which path member to update.
 *
 * If the path is successfully set, the function returns 0. If a path is
 * already set for the specified direction, the function returns 1 to
 * indicate a duplicate path setting. If an error occurs, the function
 * frees the allocated memory and returns 1.
 *
 * @param cub Pointer to the t_Cub3d structure containing program
 * context and data.
 * @param path A pointer to the current line containing the texture path.
 * @param direction An integer representing the direction identifier (1-4).
 * @return Returns 0 if the texture path is set successfully,
 * 1 if a duplicate or error occurs.
 */
static int	set_tex_path(t_Cub3d *cub, char *path, int direction)
{
	char	*temp;

	temp = ft_strdup(path + 3);
	if (direction == 1 && !cub->map->tex->path_north)
		cub->map->tex->path_north = ft_strtrim(temp, " \t");
	else if (direction == 2 && !cub->map->tex->path_south)
		cub->map->tex->path_south = ft_strtrim(temp, " \t");
	else if (direction == 3 && !cub->map->tex->path_west)
		cub->map->tex->path_west = ft_strtrim(temp, " \t");
	else if (direction == 4 && !cub->map->tex->path_east)
		cub->map->tex->path_east = ft_strtrim(temp, " \t");
	else
		return (free(temp), 1);
	return (free (temp), 0);
}

/**
 * @brief Check the validity of texture path settings for map elements.
 *
 * This function checks the correctness of texture path settings for specific
 * map elements within the scene description. It examines the provided `line`
 * to determine if it represents a valid texture path for the north (NO),
 * south (SO), west (WE), or east (EA) side of the map. If a valid texture
 * path is found, it invokes the `set_tex_path` function to store the path
 * in the appropriate member of the `t_TextureSetup` structure within the
 * provided `t_Cub3d` context. If the texture path setting is invalid or a
 * duplicate, the function returns 1 to indicate an error.
 *
 * @param cub Pointer to the t_Cub3d structure containing program
 * context and data.
 * @param line A pointer to the current line being processed from the map file.
 * @return Returns 0 if the texture path setting is valid,
 * or 1 if an error occurs.
 */
static int	has_valid_info2(t_Cub3d *cub, char *line)
{
	if (!ft_strncmp("NO ", line, 3))
	{
		if (set_tex_path(cub, line, 1))
			return (1);
	}
	else if (!ft_strncmp("SO ", line, 3))
	{
		if (set_tex_path(cub, line, 2))
			return (1);
	}
	else if (!ft_strncmp("WE ", line, 3))
	{
		if (set_tex_path(cub, line, 3))
			return (1);
	}
	else if (!ft_strncmp("EA ", line, 3))
	{
		if (set_tex_path(cub, line, 4))
			return (1);
	}
	return (0);
}

/**
 * @brief Check the validity of map information and texture settings.
 *
 * This function validates the correctness of map information and texture
 * settings within the scene description. It ensures that essential information,
 * such as texture paths and colors, is provided and correctly formatted.
 * Additionally, the function checks that the map data begins after the
 * information lines and that no invalid characters precede it.
 * It iterates through the map file until all required information is found
 * or an error is detected.
 *
 * If the information and settings are valid, the function returns 0. If any
 * checks fail, indicating invalid data or formatting, the function frees
 * allocated memory, terminates the program with an error message, and sets the
 * `crash` flag to true to indicate an error.
 *
 * @param cub Pointer to the t_Cub3d structure containing program
 * context and data.
 * @return Returns 0 if the map information and settings are valid,
 * or 1 if any checks fail.
 */
int	has_valid_info(t_Cub3d *cub)
{
	char	*line;

	ft_open(cub);
	line = get_next_line(cub->map->fd);
	while ((!cub->map->tex->path_north || !cub->map->tex->path_south
			|| !cub->map->tex->path_east || !cub->map->tex->path_west)
		|| (!cub->map->tex->colors[0] || !cub->map->tex->colors[1]))
	{
		if (ft_strchr("1\t ", line[0]))
			return (1);
		if (has_valid_info2(cub, line))
			return (1);
		else if (has_valid_info3(cub, line))
			return (1);
		free(line);
		line = get_next_line(cub->map->fd);
	}
	while (line)
	{
		free(line);
		line = get_next_line(cub->map->fd);
	}
	return (free(line), close(cub->map->fd), 0);
}
