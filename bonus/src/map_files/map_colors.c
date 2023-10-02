/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:01:39 by andvieir          #+#    #+#             */
/*   Updated: 2023/10/02 10:00:04 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d_bonus.h"

/**
 * @brief Set and store floor or ceiling color settings in the map information.
 *
 * Utility function used by `put_floor_ceil_color` to set floor or ceiling
 * color settings within the scene description. It extracts and converts
 * the RGB color components from the provided `colors` array and sets the
 * corresponding entry in the `floor_c` or `ceiling_c` array of the
 * `t_MapConfig` structure within the provided `t_Cub3d` context.
 *
 * @param cub Pointer to the t_Cub3d structure containing
 * program context and data.
 * @param n An integer indicating whether to process floor (0)
 * or ceiling (1) color.
 * @param colors Array containing RGB color components.
 */
static	void	put_floor_ceil_color_utils(t_Cub3d *cub, int n, char **colors)
{
	if (n == 0)
	{
		cub->map->floor_c[ft_atoi(colors[0])]
		[ft_atoi(colors[1])]
		[ft_atoi(colors[2])] = 1;
	}
	else
	{
		cub->map->ceilling_c[ft_atoi(colors[0])]
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
 * `t_MapConfig` structure within the provided `t_Cub3d` context.
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
			printf("Error: Invalid color range\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	if (n == 0)
		put_floor_ceil_color_utils(cub, 0, colors);
	else
		put_floor_ceil_color_utils(cub, 1, colors);
	ft_free_split(colors);
	cub->map->colors[n] = true;
}
