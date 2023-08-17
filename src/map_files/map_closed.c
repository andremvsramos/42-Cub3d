/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_closed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 11:35:38 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/08/17 17:11:16 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

static int	check_top_closed(t_Cub3d *cub)
{
	int	i;

	i = 0;
	while (cub->map->matrix[0][i])
	{
		if (!ft_strchr("1\t\n ", cub->map->matrix[0][i]))
			return (1);
		i++;
	}
	return (0);
}

static int	check_bottom_closed(t_Cub3d *cub)
{
	int	i;
	int	last_row;

	i = 0;
	last_row = cub->map->n_lines;
	while (cub->map->matrix[last_row][i])
	{
		if (!ft_strchr("1\t\n ", cub->map->matrix[last_row][i]))
			return (1);
		i++;
	}
	return (0);
}

static int	check_left_closed(t_Cub3d *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i <= cub->map->n_lines)
	{
		j = 0;
		while (j <= cub->map->max_line_len)
		{
			if (ft_strchr("\t\n ", cub->map->matrix[i][j]))
				j++;
			else if (ft_strchr("1", cub->map->matrix[i][j]))
				break;
			else
				return (1);
		}
		i++;
	}
	return (0);
}

static int	check_right_closed(t_Cub3d *cub)
{
	int	i;
	int	j;
	//int	value;

	i = 0;
	j = 0;
	//value = 0;
	while (i <= cub->map->n_lines)
	{
		j = cub->map->max_line_len;
		while (j >= 0)
		{
			if (ft_strchr("\t\n ", cub->map->matrix[i][j]))
				j--;
			else if (ft_strchr("1", cub->map->matrix[i][j]))
				break;
			else
				return (1);
		}
		i++;
	}
	return (0);
}

void	check_map_closed(t_Cub3d *cub)
{
	if (check_top_closed(cub) || check_bottom_closed(cub) ||
		check_right_closed(cub) || check_left_closed(cub))
	{
		free_main(cub);
		shutdown("Error: Map is not surounded by walls!\n", true);
	}
}
