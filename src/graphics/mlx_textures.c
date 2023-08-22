/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Untitled-1                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:10:04 by marvin            #+#    #+#             */
/*   Updated: 2023/08/20 17:10:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

/* void	convert_textures(t_Cub3d *cub)
{
	mlx_xpm_to_image()
	mlx_xpm_file_to_image(cub->mlx_ptr, cub->map->tex->path_north);
	mlx_xpm_file_to_image(cub->mlx_ptr, cub->map->tex->path_south);
	mlx_xpm_file_to_image(cub->mlx_ptr, cub->map->tex->path_west);
	mlx_xpm_file_to_image(cub->mlx_ptr, cub->map->tex->path_east);
}
 */

/**
 * @brief Check if a given file path corresponds to an XPM image file.
 *
 * This function checks whether the given file path corresponds to an XPM image
 * file based on its extension. It compares the file extension with ".xpm" and
 * returns 1 if the file is an XPM image, or 0 if it's not.
 *
 * @param cub Pointer to the t_Cub3d structure containing program context and
 * data.
 * @param id The ID corresponding to the texture path to be checked:
 *  1 for north texture, 2 for south texture, 3 for west texture, 4 for
 * east texture.
 * @return Returns 1 if the file path corresponds to an XPM image,
 * or 0 otherwise.
 */
int	is_xpm(t_Cub3d *cub, int id)
{
	char	*filetype;
	char	*filename;
	int		len;
	int		i;

	filetype = ".xpm";
	if (id == 1)
		filename = ft_strdup(cub->map->tex->path_north);
	else if (id == 2)
		filename = ft_strdup(cub->map->tex->path_south);
	else if (id == 3)
		filename = ft_strdup(cub->map->tex->path_west);
	else if (id == 4)
		filename = ft_strdup(cub->map->tex->path_east);
	i = 4;
	len = ft_strlen(filename) - 1;
		if (filename[len] == '\n')
			len--;
	while (i)
		if (filename[len--] != filetype[--i])
			return (free(filename), 1);
	return (free(filename), 0);
}

/**
 * @brief Check the validity of texture file paths.
 *
 * This function checks the validity of the texture file paths in the t_Cub3d
 * structure. It calls the is_xpm function for each texture path (north, south,
 * west, and east), and returns 1 if any of the texture paths are not XPM
 * images, indicating an invalid texture.
 * If all texture paths are valid XPM images, it returns 0.
 *
 * @param cub Pointer to the t_Cub3d structure containing program context
 * and data.
 * @return Returns 1 if any of the texture paths are invalid XPM images, or 0
 * if all are valid.
 */
int	check_tex_validity(t_Cub3d *cub)
{
	if (is_xpm(cub, 1) || is_xpm(cub, 2)
		|| is_xpm(cub, 3) || is_xpm(cub, 4))
		return (1);
	//convert_textures(cub);
	return (0);
}
