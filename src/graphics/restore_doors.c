/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_doors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:59:00 by andvieir          #+#    #+#             */
/*   Updated: 2023/09/22 11:31:31 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

int		check_walls_doors(t_MapConfig *m, int i, int j)
{
	if (m->matrix[i][j] == '9')
	{
		if (BONUS)
		{
			if (m->matrix[i][j - 1] == '0' && m->matrix[i][j + 1] == '0' &&
				m->matrix[i - 1][j] == '1' && m->matrix[i + 1][j] == '1')
				return (0);
			else if (m->matrix[i][j - 1] == '1' && m->matrix[i][j + 1] == '1' &&
				m->matrix[i - 1][j] == '0' && m->matrix[i + 1][j] == '0')
				return (0);
			else
				return (1);
		}
		else
			return (1);
	}
	return (0);
}

void	restore_doors(t_Cub3d *cub)
{
	char	*line;
	int		y;
	int		x;

	cub->map->temp_fd = open("./.map", O_RDONLY);
	line = get_next_line(cub->map->temp_fd);
	if (!line)
		return ;
	y = 0;
	while (line)
	{
		x = 0;
		while (line[x])
		{
			if (line[x] == '9')
			{
				if (cub->map->matrix[y][x] == '0'
					&& (cub->player->pos_y > y + 3
						|| cub->player->pos_y < y - 3
						|| cub->player->pos_x > x + 3
						|| cub->player->pos_x < x - 3))
					cub->map->matrix[y][x] = '9';
			}
			x++;
		}
		y++;
		free(line);
		line = get_next_line(cub->map->temp_fd);
	}
}
