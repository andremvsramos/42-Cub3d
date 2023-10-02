/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:57:34 by andvieir          #+#    #+#             */
/*   Updated: 2023/10/02 10:20:01 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d_bonus.h"

/**
 * @brief Clean up and release resources used by the Get Next Line (GNL)
 * function.
 *
 * The `ft_clean_gnl` function is responsible for freeing memory and closing the
 * file descriptor associated with the Get Next Line (GNL) function. It iterates
 * through the GNL output lines, freeing each line's memory, and then closes the
 * file descriptor. This function should be called when GNL is no longer needed
 * to prevent memory leaks and resource leaks.
 *
 * @param fd The file descriptor associated with the GNL function.
 * @param line A pointer to the last GNL output line or NULL if GNL is not in
 * use.
 */
void	ft_clean_gnl(int fd, char *line)
{
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

/**
 * @brief Open the map file for reading.
 *
 * This function opens the map file specified in the `filename` member of the
 * `t_MapConfig` structure within the provided `t_Cub3d` context.
 * It uses the O_RDONLY flag to open the file for reading only. If the file
 * cannot be opened, the function frees allocated memory, terminates the
 * program with an error message, and sets the `crash` flag to true to indicate
 * an error.
 *
 * @param cub Pointer to the t_Cub3d structure containing
 * program context and data.
 */
void	ft_open(t_Cub3d *cub)
{
	cub->map->fd = open(cub->map->filename, O_RDONLY);
	if (cub->map->fd < 0)
	{
		free_main(cub);
		printf("Error: fatal: cannot open map file\n");
		exit(EXIT_FAILURE);
	}
}

/**
 * Creates a temporary map file containing the map data extracted from the
 * original map file.
 *
 * @param cub  A pointer to the Cub3d structure.
 * @param line The current line of data from the original map file.
 *
 * @note This function opens a temporary map file named "./.map" and writes the
 * map data extracted from the original map file into it. The function continues
 * reading lines from the original map file using the `get_next_line` function
 * and writing them to the temporary map file until the end ofthe file is
 * reached. The provided `line` pointer will be freed after each write operation
 */
void	create_temp_map(t_Cub3d *cub, char *line)
{
	cub->map->temp_fd = open("./.map", O_RDWR | O_CREAT
			| O_TRUNC, S_IRUSR | S_IWUSR);
	while (line)
	{
		write(cub->map->temp_fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(cub->map->fd);
	}
}

/**
 * @brief Helper function to skip over map information lines.
 *
 * This helper function is used by the skip_info function to process map
 * information lines and update the skip counter accordingly. It checks for
 * various prefixes associated with texture paths and color settings,
 * incrementing the skip counter when these lines are encountered.
 * Additionally, it ensures that the first line of map data (containing '1'
 * for walls) is correctly located and not skipped.
 *
 * @param cub Pointer to the t_Cub3d structure containing program
 * context and data.
 * @param line A pointer to the current line being processed from the map file.
 * @param skip A pointer to the skip counter, updated during the process.
 * @return Returns a pointer to the next line after processing.
 */
static char	*skip_info2(t_Cub3d *cub, char *line, int *skip)
{
	if (ft_strchr("\n", line[0]))
	{
		cub->map->skip_counter++;
		free(line);
		line = get_next_line(cub->map->fd);
	}
	if (!ft_strncmp("NO ", line, 3) || !ft_strncmp("SO ", line, 3)
		|| !ft_strncmp("WE ", line, 3) || !ft_strncmp("EA ", line, 3)
		|| !ft_strncmp("F ", line, 2) || !ft_strncmp("C ", line, 2)
		|| (BONUS && !ft_strncmp("DO ", line, 3)))
		(*skip)++;
	if (ft_strchr("1\t ", line[0]) && *skip != SKIP + BONUS - 1)
		return (NULL);
	cub->map->skip_counter++;
	free(line);
	line = get_next_line(cub->map->fd);
	return (line);
}

/**
 * @brief Skip over map information lines and locate the start of the map data.
 *
 * This function is responsible for reading through the map file and skipping
 * over the initial map information lines, such as texture paths and color
 * settings. It continues to traverse the file until it locates the first line
 * of actual map data containing '1' to represent walls. Once the first map data
 * line is found, the function returns a pointer to it, allowing subsequent
 * processing of the map layout.
 * The function utilizes a skip counter to keep track ofthe number of lines
 * skipped during the process.
 *
 * @param cub Pointer to the t_Cub3d structure containing
 * program context and data.
 * @param line A pointer to the current line being processed from the map file.
 * @return Returns a pointer to the first line of actual map data, or NULL if
 * not found.
 */
char	*skip_info(t_Cub3d *cub, char *line, int i)
{
	int	skip;

	skip = 0;
	while (skip < SKIP + BONUS)
		line = skip_info2(cub, line, &skip);
	if (!line)
		return (NULL);
	while (ft_strchr("\n", line[0]))
	{
		free(line);
		line = get_next_line(cub->map->fd);
	}
	while (line)
	{
		i = 0;
		while (line[i])
		{
			if (!ft_strncmp("1", &line[i], 1))
				return (line);
			i++;
		}
		free(line);
		line = get_next_line(cub->map->fd);
	}
	return (NULL);
}
