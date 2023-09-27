/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_closed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 11:35:38 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/09/27 23:30:04 by marvin           ###   ########.fr       */
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
 * @brief Check the surroundings of a character in the map matrix.
 *
 * The `check_surroundings` function examines the neighboring characters of a
 * specific character in the game map's matrix. It verifies whether the
 * character complies with the rules of a valid map layout, including walls,
 * doors, and empty spaces. If any inconsistencies or errors are detected in
 * the surroundings, the function returns an error code.
 *
 * @param m Pointer to the map configuration.
 * @param i The row index of the character to check.
 * @param j The column index of the character to check.
 * @return 1 if the surroundings are invalid, 0 if they are valid.
 */
int	check_surroundings(t_MapConfig *m, int i, int j)
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
 * @brief Check the validity of door placements in the map.
 *
 * The `check_closed` function scans the map matrix to verify if the placement
 * of doors is valid. It checks whether doors have one of two specific setups:
 * an available path from north to south while having walls on the east and west
 * sides, or walls on the north and south sides with a path to the east and
 * west. If these conditions are not met, the function returns an error code,
 * indicating an invalid door placement.
 *
 * @param m Pointer to the map configuration struct.
 * @param i The row index of the current character.
 * @param j The column index of the current character.
 * @return 1 if the door placement is invalid, 0 if it is valid.
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
			if (check_surroundings_utils(m, i, j, charset))
				return (1);
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
