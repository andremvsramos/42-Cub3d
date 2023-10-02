/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_parser_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 22:29:46 by marvin            #+#    #+#             */
/*   Updated: 2023/09/27 22:29:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d_bonus.h"

/**
 * @brief Check and set the texture path for the north and south walls.
 *
 * The `check_north_south` function checks if the given line corresponds to the
 * texture path for the north or south walls (e.g., "NO texture_path" or
 * "SO texture_path"). If a valid path is found, it calls `set_tex_path` to set
 * the appropriate texture path in the `cub` configuration.
 *
 * @param cub Pointer to the main Cub3D configuration.
 * @param line The line from the map file being processed.
 * @return 1 if an error occurs (e.g., invalid path), 0 otherwise.
 */
int	check_north_south(t_Cub3d *cub, char *line)
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
	return (0);
}

/**
 * @brief Check and set the texture path for the west and east walls.
 *
 * The `check_west_east` function checks if the given line corresponds to the
 * texture path for the west or east walls (e.g., "WE texture_path" or
 * "EA texture_path"). If a valid path is found, it calls `set_tex_path` to set
 * the appropriate texture path in the `cub` configuration.
 *
 * @param cub Pointer to the main Cub3D configuration.
 * @param line The line from the map file being processed.
 * @return 1 if an error occurs (e.g., invalid path), 0 otherwise.
 */
int	check_west_east(t_Cub3d *cub, char *line)
{
	if (!ft_strncmp("WE ", line, 3))
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
 * @brief Fill in bonus information in the Cub3D configuration.
 *
 * The `fill_bonus_info` function extracts and fills bonus-related information
 * in the `cub` configuration, such as texture paths and colors. It continues
 * reading lines from the map file until all the required bonus information is
 * found or until an error occurs. This function is used during map file
 * parsing.
 *
 * @param cub Pointer to the main Cub3D configuration.
 * @param line The current line being processed from the map file.
 * @return 1 if an error occurs, 0 otherwise.
 */
int	fill_bonus_info(t_Cub3d *cub, char *line)
{
	while ((!cub->map->tex_north->path || !cub->map->tex_south->path
			|| !cub->map->tex_west->path || !cub->map->tex_east->path)
		|| (!cub->map->colors[0] || !cub->map->colors[1])
		|| !cub->map->tex_door->path)
	{
		if (!line)
			return (ft_clean_gnl(cub->map->fd, line), 1);
		if (ft_strchr("1\t ", line[0]))
			return (ft_clean_gnl(cub->map->fd, line), 1);
		if (has_valid_info2(cub, line))
			return (ft_clean_gnl(cub->map->fd, line), 1);
		else if (has_valid_info3(cub, line))
			return (ft_clean_gnl(cub->map->fd, line), 1);
		free(line);
		line = get_next_line(cub->map->fd);
	}
	ft_clean_gnl(cub->map->fd, line);
	return (0);
}
