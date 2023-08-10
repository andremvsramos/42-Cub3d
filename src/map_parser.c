/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:20:46 by andvieir          #+#    #+#             */
/*   Updated: 2023/08/10 16:20:46 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

/**
 * @brief Check if a given file name has a valid map type for the Cub3D project.
 *
 * This function checks whether the provided file name has a valid map type,
 * indicated by the ".cub" extension. It compares the characters in reverse order,
 * starting from the end of the file name, with the characters in the ".cub" extension.
 *
 * @param FileName Pointer to the null-terminated string representing the file name.
 * @return 1 if the file name has a valid map type, 0 if not.
 */
int	isValidMapType(char *FileName)
{
	char	*FileType;
	int		len;
	int		i;

	FileType = ".cub";
	len = ft_strlen(FileName) - 1;
	i = 4;
	while (i)
		if (FileName[len--] != FileType[--i])
			return (1)
	return (0);
}

/**
 * @brief Parse and validate the scene description map file for the Cub3D project.
 *
 * This function is responsible for parsing the provided scene description map file.
 * It reads and validates the map file's content, ensuring it adheres to the specified rules,
 * such as the correct map structure and element order. It also validates that the file is
 * of the correct type (".cub" extension).
 *
 * If the map file is valid, the function should populate the appropriate data structures
 * within the `t_Cub3d` object passed as `cub`. If the file is invalid or cannot be read,
 * the function frees allocated memory, terminates the program with an error message,
 * and sets the `crash` flag to true to indicate an error.
 *
 * @param cub Pointer to the t_Cub3d structure containing program context and data.
 */
int	parseMapFile(t_Cub3d *cub)
{

	if (!cub->FileName || isValidMapFile(cub->FileName))
	{
		free(cub->FileName);
		free(cub);
		shutdown("Error: Cannot read map file or is of wrong type\n", true);
	}

	// TODO: Implement map file parsing and validation logic here.

}
