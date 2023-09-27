/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_closed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 11:35:38 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/09/27 20:03:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

/**
 * @brief Check if the top and bottom boundaries of the map are closed.
 *
 * This function checks if the top and bottom boundaries of the map are properly
 * closed, ensuring that all elements along these boundaries are either '1'
 * (wall) or empty space ' '. If any other characters are found along these
 * boundaries, the function returns 1 to indicate an error. Otherwise, it
 * returns 0 to indicate successful validation.
 *
 * @param cub Pointer to the t_Cub3d structure containing
 * program context and data.
 * @return Returns 0 if the top and bottom boundaries are closed properly,
 * or 1 if an error is detected.
 */
static int	check_top_bot_closed(t_MapConfig *m)
{
	int	i;
	int	last_row;

	i = 0;
	last_row = m->n_lines;
	while (m->matrix[0][i])
	{
		if (!ft_strchr("1 ", m->matrix[0][i]))
			return (1);
		i++;
	}
	i = 0;
	while (m->matrix[last_row][i])
	{
		if (!ft_strchr("1 ", m->matrix[last_row][i]))
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Check the surroundings of a map element for validity.
 *
 * This function evaluates the surroundings of a map element at position (i, j)
 * to ensure the integrity of the map structure. It examines whether the element
 * is a wall ('1'), a traversable area ('0'), the player spawn point
 * ('N', 'S', 'E', 'W'), or an empty space (' ').
 *
 * For traversable areas ('0') and player spawn points ('N', 'S', 'E', 'W'), the
 * function checks if any adjacent elements are empty spaces (' '). Such a
 * configuration would violate the rule that the map must be enclosed by walls
 * and that traversable areas should not have empty spaces inside them. If such
 * an inconsistency is found, the function returns 1, indicating an error in the
 * map layout. Otherwise, it returns 0, confirming that the surroundingsare
 * valid.
 *
 * @param cub Pointer to the t_Cub3d structure containing program context
 * and data.
 * @param i Row index of the map element.
 * @param j Column index of the map element.
 * @return Returns 0 if surroundings are valid, or 1 if an error is detected.
 */
static int	check_surroundings(t_MapConfig *m, int i, int j)
{
	char	*charset;

	charset = "0NSEW";
	if (BONUS)
		charset = "09NSEW";
	if ('1' == m->matrix[i][j])
		return (0);
	else if (ft_strchr(charset, m->matrix[i][j]))
	{
		if (j == 0 && (m->matrix[i][j] != '1' || m->matrix[i][j] != ' '))
			return (1);
		get_matrix_borders(m, i, j);
		if ((m->up_valid && m->matrix[i - 1][j] == ' ')
			|| (m->down_valid && m->matrix[i + 1][j] == ' ')
			|| (m->left_valid && m->matrix[i][j - 1] == ' ')
			|| (m->right_valid && m->matrix[i][j + 1] == ' '))
			return (1);
		if (check_walls_doors(m, i, j))
				return (1);
	}
	else if (ft_strchr("\n\t ", m->matrix[i][j]))
		return (0);
	return (0);
}

/**
 * @brief Check for invalid whitespace between walls in the map.
 *
 * This function checks for the presence of invalid whitespace between walls
 * within the map matrix. It examines whether a space (' ') is encountered and
 * verifies if the element to its left is '0', indicating a void space between
 * walls. Such void spaces can result in an unenclosed map layout. If both
 * conditions are met, the function returns 1 to indicate an error.
 *
 * The function also handles the traversal to the next line in the matrix if the
 * end of the line is reached (when j equals the maximum line length), updating
 * the row index (*i) and resetting the column index (j) accordingly.
 *
 * @param cub Pointer to the t_Cub3d structure containing
 * program context and data.
 * @param i Pointer to the current row index in the matrix.
 * @param j Current column index in the matrix.
 * @return Returns 1 if an invalid whitespace between walls is
 * found, or 0 otherwise.
 */
static int	check_nullb_whitespaces(t_MapConfig *m, int *i, int *j)
{
	if (*j == m->max_line_len)
		return ((*i)++, *j = 0, 0);
	if (ft_strchr(" ", m->matrix[*i][*j]) && *j == 0)
		return (0);
	if (ft_strchr(" ", m->matrix[*i][*j])
		&& ft_strchr("09", m->matrix[*i][*j - 1]))
		return (1);
	return (0);
}

/**
 * @brief Check if the map is fully enclosed by walls and has valid player
 * movement areas.
 *
 * This function checks whether the map is fully enclosed by walls and has
 * valid player movement areas. It iterates through the map matrix and examines
 * each element to ensure that walls are present at the boundaries and that the
 * player movement areas are defined by '0' characters. The function calls
 * helper functions to perform specific checks:
 * - `check_nullb_whitespaces` detects invalid whitespace between walls.
 * - `check_surroundings` verifies the surroundings of a given element for valid
 * player movement.
 *
 * If any discrepancies are found, the function returns 1 to indicate an error.
 *
 * @param cub Pointer to the t_Cub3d structure containing program
 * context and data.
 * @param i Starting row index for iterating through the map matrix.
 * @param j Starting column index for iterating through the map matrix.
 * @return Returns 1 if the map is not properly enclosed or has invalid player
 * movement areas, or 0 if the map is correctly enclosed and has valid player
 * movement areas.
 */
static int	check_closed(t_MapConfig *m, int i, int j)
{
	char	*charset;

	charset = "0NSEW";
	if (BONUS)
		charset = "09NSEW";
	while (i <= m->n_lines - 1)
	{
		j = 0;
		while (j <= m->max_line_len - 1)
		{
			if (check_nullb_whitespaces(m, &i, &j))
				return (1);
			if (i > m->n_lines)
				break ;
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
			j++;
		}
		i++;
	}
	return (0);
}

/**
 * @brief Check map enclosure and valid player movement areas.
 *
 * This function verifies if the map is enclosed by walls and has valid player
 * movement areas. It uses the `check_top_bot_closed` and `check_closed`
 * functions for these checks.
 *
 * @param cub Pointer to the t_Cub3d structure.
 * @return Returns 1 if map is not enclosed or has invalid movement areas, else
 * returns 0.
 */
int	check_map_closed(t_Cub3d *cub)
{
	if (check_top_bot_closed(cub->map) || check_closed(cub->map, 1, 0))
		return (1);
	return (0);
}
