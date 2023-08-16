/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_matrix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 11:39:08 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/08/16 11:57:13 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

int	fill_matrix(t_Cub3d *cub)
{
	int	i;

	i = 0;
	cub->map->matrix = ft_calloc(cub->map->n_lines, sizeof(char *));
	while (i < cub->map->n_lines)
		cub->map->matrix[i++] = ft_calloc(cub->map->max_line_len, sizeof(char));
}
