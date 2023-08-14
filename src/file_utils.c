/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:57:34 by andvieir          #+#    #+#             */
/*   Updated: 2023/08/14 18:10:22 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

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
		shutdown("Error: fatal: cannot open map file\n", true);
	}
}

/**
 * @brief Skip over map information lines and locate the start of the map data.
 *
 * This function reads through the map file to skip over the initial map
 * information lines, such as texture paths and color settings, until it locates
 * the first line of actual map data (containing '1' representing walls). It
 * then returns a pointer to this first map data line, allowing subsequent
 * processing of the map layout. The function utilizes a skip counter to keep
 * track of the number of lines skipped during the process.
 *
 * @param cub Pointer to the t_Cub3d structure containing program context and data.
 * @param line A pointer to the current line being processed from the map file.
 * @return Returns a pointer to the first line of actual map data, or NULL if not found.
 */
char	*skip_info(t_Cub3d *cub, char *line)
{
	int	skip;
	int	i;

	skip = 0;
	while (skip < 6)
	{
		if(ft_strchr("\n", line[0]))
		{
			free(line);
			line = get_next_line(cub->map->fd);
		}
		if (!ft_strncmp("NO ", line, 3) || !ft_strncmp("SO ", line, 3)
			|| !ft_strncmp("WE ", line, 3) || !ft_strncmp("EA ", line, 3)
			|| !ft_strncmp("F ", line, 2) || !ft_strncmp("C ", line, 2))
			skip++;
		if (ft_strchr("1\t ", line[0]) && skip != 5)
			return (NULL);
		free(line);
		line = get_next_line(cub->map->fd);
	}
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
			{
				puts(&line[i]);
				return (line);
			}
			i++;
		}
		free(line);
		line = get_next_line(cub->map->fd);
	}
	//CRIAR SKIP COUNTER NA ESTRUTUTRA PARA ALTERAR NAS VALID BOUNDARIES O VALOR DO INDEX,
	// NAO PODE SER 0
	return (line);
}
