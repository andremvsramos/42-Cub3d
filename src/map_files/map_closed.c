/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_closed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 11:35:38 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/08/18 18:11:07 by andvieir         ###   ########.fr       */
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

static int	check_surroundings(t_Cub3d *cub, int i, int j)
{
	//puts(&cub->map->matrix[i][j]);
	if (ft_strchr("1", cub->map->matrix[i][j]))
		return (0);
	else if (ft_strchr("0NSEW", cub->map->matrix[i][j]))
	{

		if (ft_strchr(" ", cub->map->matrix[i - 1][j])
			|| ft_strchr(" ", cub->map->matrix[i + 1][j])
			|| ft_strchr(" ", cub->map->matrix[i][j - 1])
			|| ft_strchr(" ", cub->map->matrix[i][j + 1]))
		{
			printf("MATRIX[%d][%d] = %c\n", i - 1, j, cub->map->matrix[i - 1][j]);
			printf("MATRIX[%d][%d] = %c\n", i + 1, j, cub->map->matrix[i + 1][j]);
			printf("MATRIX[%d][%d] = %c\n", i, j - 1, cub->map->matrix[i][j - 1]);
			printf("MATRIX[%d][%d] = %c\n", i, j + 1, cub->map->matrix[i][j + 1]);
			return (1);
		}
	}
	else if (ft_strchr("\n\t ", cub->map->matrix[i][j]))
		return (0);
	return (0);
}

static int	check_closed(t_Cub3d *cub)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i <= cub->map->n_lines - 1)
	{
		j = 0;
		while (j <= cub->map->max_line_len)
		{
			if (ft_strchr("\t\n ", cub->map->matrix[i][j])
				&& ft_strchr("0", cub->map->matrix[i][j - 1]))
				return (printf("1 FODEU NA MATRIX[%d][%d] = %c\n", i, j, cub->map->matrix[i][j]), 1);
			else
				j++;
			if (ft_strchr("1", cub->map->matrix[i][j]))
			{
				if (check_surroundings(cub, i, ++j))
					return (printf("1 FODEU NA MATRIX[%d][%d] = %c\n", i, j, cub->map->matrix[i][j]), 1);
				j++;
			}
			else if (ft_strchr("0NSEW", cub->map->matrix[i][j]))
			{
				if (check_surroundings(cub, i, j))
					return (printf("0 FODEU NA MATRIX[%d][%d] = %c\n", i, j, cub->map->matrix[i][j]), 1);
				j++;
			}
		}
		i++;
	}
	return (0);
}

int	check_map_closed(t_Cub3d *cub)
{
	if (check_top_closed(cub) || check_bottom_closed(cub) ||
		check_closed(cub))
		return (1);
	return (0);
}
