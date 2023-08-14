/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:45:39 by andvieir          #+#    #+#             */
/*   Updated: 2023/08/14 17:44:53 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	put_floor_ceil_color(t_Cub3d *cub, char *line, int n)
{
	char	**colors;

	colors = ft_split(line + 2, ',');
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
	ft_free_split(colors);
	cub->map->tex->colors[n] = true;
}

static int	has_valid_info3(t_Cub3d *cub, char *line)
{
	if (!ft_strncmp("F ", line, 2))
	{
		if (!cub->map->tex->colors[0])
			put_floor_ceil_color(cub, line, 0);
		else return (1);
	}
	else if (!ft_strncmp("C ", line, 2))
	{
		if (!cub->map->tex->colors[1])
			put_floor_ceil_color(cub, line, 1);
		else return (1);
	}
	return (0);
}

static int	has_valid_info2(t_Cub3d *cub, char *line)
{
	if (!ft_strncmp("NO ", line, 3))
	{
		if (!cub->map->tex->path_north)
			cub->map->tex->path_north = ft_strdup(line + 3);
		else return (1);
	}
	else if (!ft_strncmp("SO ", line, 3))
	{
		if (!cub->map->tex->path_south)
			cub->map->tex->path_south = ft_strdup(line + 3);
		else return (1);
	}
	else if (!ft_strncmp("WE ", line, 3))
	{
		if (!cub->map->tex->path_west)
			cub->map->tex->path_west = ft_strdup(line + 3);
		else return (1);
	}
	else if (!ft_strncmp("EA ", line, 3))
	{
		if (!cub->map->tex->path_east)
			cub->map->tex->path_east = ft_strdup(line + 3);
		else return (1);
	}
	return (0);
}

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
	return (free(line), close(cub->map->fd), 0);
}
