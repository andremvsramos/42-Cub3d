/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Untitled-1                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 22:43:09 by marvin            #+#    #+#             */
/*   Updated: 2023/09/27 22:43:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d_bonus.h"

/**
 * @brief Check the surroundings of a specified character in the map.
 *
 * The `check_surroundings_utils` function examines the surrounding tiles
 * of a specified character within the map matrix to verify that it is
 * placed in a valid context. It is typically used to check if characters
 * like '0', 'N', 'S', 'W', and 'E' have appropriate neighboring tiles,
 * such as walls or other valid characters. If the surroundings are
 * invalid, the function returns an error.
 *
 * @param m Pointer to the map configuration.
 * @param i The row index of the character.
 * @param j The column index of the character.
 * @param charset A string containing valid characters for the surroundings.
 * @return 1 if the surroundings are invalid, 0 if they are valid.
 */
int	check_surroundings_utils(t_MapConfig *m, int i, int j, char *charset)
{
	if ('1' == m->matrix[i][j])
	{
		if (check_surroundings(m, i, j))
			return (1);
	}
	else if (ft_strchr(charset, m->matrix[i][j])
		&& m->matrix[i][j])
	{
		if (check_surroundings(m, i, j))
			return (1);
	}
	return (0);
}
