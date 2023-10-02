/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_matrix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 11:39:08 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/10/02 10:00:09 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d_bonus.h"

/**
 * @brief Fill the game map matrix with characters, handling newline characters.
 *
 * The `fill_matrix3` function is responsible for filling the game map matrix
 * with characters. It processes each character (including newline characters)
 * from the map file and stores them in the appropriate positions of the matrix.
 *
 * When encountering a newline character ('\n'), the function ensures that the
 * remaining positions in the current row of the matrix are filled with spaces
 * (' ') to align the matrix properly.
 *
 * @param cub Pointer to the main game structure.
 * @param c The character to be added to the matrix (including '\n' for
 * newlines).
 * @param y The current row index in the matrix.
 * @param x Pointer to the current column index in the matrix.
 */
static void	fill_matrix3(t_Cub3d *cub, char c, int y, int *x)
{
	if (c == '\n')
		while (*x < cub->map->max_line_len - 1)
			cub->map->matrix[y][(*x)++] = ' ';
	else
	{
		cub->map->matrix[y][(*x)] = c;
		if (*x < cub->map->max_line_len - 1)
			(*x)++;
	}
}

/**
 * @brief Fill the game map matrix with formatted data from a line.
 *
 * The `fill_matrix2` function is responsible for parsing a line of formatted
 * data and filling the game map matrix accordingly. It processes the line
 * character by character, handling tabs and regular characters differently.
 * When a tab character is encountered, it ensures that the corresponding number
 * of spaces is inserted into the matrix. For non-tab characters, it delegates
 * the task to the `fill_matrix3` function to handle map data formatting. This
 * function is crucial for correctly initializing the game map for rendering.
 *
 * @param cub Pointer to the `t_Cub3d` structure containing program context and
 * data.
 * @param line A pointer to the input line containing map data.
 * @param y The current row index within the map matrix.
 * @param x A pointer to the current column index within the map matrix.
 */
static void	fill_matrix2(t_Cub3d *cub, char *line, int y, int x)
{
	int	i;
	int	tabs;

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
				cub->map->matrix[y][x++] = ' ';
			tabs = 0;
		}
		else
		{
			if (tabs >= 7)
				tabs = 0;
			fill_matrix3(cub, line[i], y, &x);
		}
		i++;
	}
	cub->map->matrix[y][cub->map->max_line_len - 1] = '\0';
}

/**
 * @brief Fill the map matrix with data from the map file.
 *
 * This function reads the map file line by line using the get_next_line
 * function and fills the cub->map->matrix data structure with the characters
 * from the map file. It allocates memory for each row in the matrix and calls
 * the fill_matrix2 function to process each character in the line and fill the
 * corresponding matrix positions. After processing each line, it increments the
 * row index and frees allocated memory.
 *
 * @param cub Pointer to the t_Cub3d structure containing program context
 * and data.
 * @return Returns 0 if the matrix is successfully filled, or 1 in case of an
 * error.
 */
int	fill_matrix(t_Cub3d *cub)
{
	int		y;
	char	*line;

	y = 0;
	cub->map->temp_fd = open("./.map", O_RDONLY);
	line = get_next_line(cub->map->temp_fd);
	if (!line)
		return (1);
	cub->map->matrix = ft_calloc(cub->map->n_lines + 1, sizeof(char *));
	while (line)
	{
		cub->map->matrix[y] = ft_calloc(cub->map->max_line_len + 1,
				sizeof(char));
		fill_matrix2(cub, line, y, 0);
		y++;
		free(line);
		line = get_next_line(cub->map->temp_fd);
	}
	return (free(line), close(cub->map->temp_fd), 0);
}
