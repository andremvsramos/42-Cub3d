/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_matrix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 11:39:08 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/08/18 18:14:25 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

static void	fill_matrix2(t_Cub3d *cub, char *line, int y)
{
	int	x;
	int	i;
	int	tabs;

	x = 0;
	i = 0;
	tabs = 0;
	while (line[i])
	{
		tabs++;
		if (line[i] == '\t')
		{
			if (tabs == 8)
				tabs = 0;
			while (tabs++ <= 8)
				cub->map->matrix[y][x] = ' ';
			tabs = 0;
		}
		else
		{
			cub->map->matrix[y][x] = line[i];
			x++;
		}
		i++;
	}
}

int	fill_matrix(t_Cub3d *cub)
{
	int		y;
	char	*line;

	y = 0;
	cub->map->temp_fd = open("./.map", O_RDONLY);
	line = get_next_line(cub->map->temp_fd);
	if (!line)
		return (free(line), 1);
	cub->map->matrix = ft_calloc(cub->map->n_lines + 1, sizeof(char *));
	while (line)
	{
		cub->map->matrix[y] = ft_calloc(cub->map->max_line_len + 1, sizeof(char));
		fill_matrix2(cub, line, y);
		//puts(cub->map->matrix[y]);
		y++;
		free(line);
		line = get_next_line(cub->map->temp_fd);
	}
	return (free(line), close(cub->map->temp_fd), 0);
}
