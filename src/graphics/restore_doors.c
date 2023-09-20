/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_doors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:59:00 by andvieir          #+#    #+#             */
/*   Updated: 2023/09/20 19:11:11 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

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
