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

/**
 * @brief Check access to texture files within the Cub3D application.
 *
 * The `check_access` function is responsible for verifying the accessibility
 * of the texture files used in the Cub3D application. It attempts to open each
 * of the four provided texture paths using the `O_RDONLY` flag and stores the
 * corresponding file descriptors. After attempting to open all the files, the
 * function closes the opened file descriptors. If any of the files cannot be
 * opened or accessed, the function returns 1 to indicate an error; otherwise,
 * it returns 0 to indicate successful access.
 *
 * @param cub Pointer to the `t_Cub3d` structure containing program context and
 * data.
 * @return Returns 0 if access to all texture files is successful, or 1 if
 * there's an error accessing any of the files.
 */
int	check_access(t_Cub3d *cub)
{
	int	fd[4];

	fd[0] = open(cub->map->tex_north->path, O_RDONLY);
	fd[1] = open(cub->map->tex_south->path, O_RDONLY);
	fd[2] = open(cub->map->tex_west->path, O_RDONLY);
	fd[3] = open(cub->map->tex_east->path, O_RDONLY);
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
	close(fd[3]);
	if (fd[0] < 0 || fd[1] < 0 || fd[2] < 0 || fd[3] < 0)
		return (1);
	return (0);
}

static int	convert_textures(t_Cub3d *cub)
{
	cub->map->tex_north->img->width = 0;
	cub->map->tex_north->img->height = 0;
	cub->map->tex_north->xpm = mlx_xpm_file_to_image(cub->win->mlx_ptr,
		cub->map->tex_north->path, &cub->map->tex_north->img->width, &cub->map->tex_north->img->height);/*
	cub->map->tex_south->xpm = mlx_xpm_file_to_image(cub->mlx_ptr,
		cub->map->tex_south->path, &cub->map->tex_south->img->width, &cub->map->tex_south->img->height);
	cub->map->tex_west->xpm = mlx_xpm_file_to_image(cub->mlx_ptr,
		cub->map->tex_west->path, &cub->map->tex_west->img->width, &cub->map->tex_west->img->height);
	cub->map->tex_east->xpm = mlx_xpm_file_to_image(cub->mlx_ptr,
		cub->map->tex_east->path, &cub->map->tex_east->img->width, &cub->map->tex_east->img->height); */
	if (!cub->map->tex_north->xpm /* || !cub->map->tex_south->xpm
		|| !cub->map->tex_west->xpm || !cub->map->tex_east->xpm */)
		return (1);
	cub->map->tex_north->img->addr = mlx_get_data_addr(&cub->map->tex_north->xpm,
		&cub->map->tex_north->img->bpp, &cub->map->tex_north->img->len, &cub->map->tex_north->img->endian);/*
	cub->map->tex_south->img->addr = mlx_get_data_addr(&cub->map->tex_south->img->img_ptr,
		&cub->map->tex_south->img->bpp, &cub->map->tex_south->img->len, &cub->map->tex_south->img->endian);
	cub->map->tex_west->img->addr = mlx_get_data_addr(&cub->map->tex_west->img->img_ptr,
		&cub->map->tex_west->img->bpp, &cub->map->tex_west->img->len, &cub->map->tex_west->img->endian);
	cub->map->tex_east->img->addr = mlx_get_data_addr(&cub->map->tex_east->img->img_ptr,
		&cub->map->tex_east->img->bpp, &cub->map->tex_east->img->len, &cub->map->tex_east->img->endian); */
	return (0);
}


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
		filename = ft_strdup(cub->map->tex_north->path);
	else if (id == 2)
		filename = ft_strdup(cub->map->tex_south->path);
	else if (id == 3)
		filename = ft_strdup(cub->map->tex_west->path);
	else if (id == 4)
		filename = ft_strdup(cub->map->tex_east->path);
	i = 4;
	len = ft_strlen(filename) - 1;
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
	cub->map->tex_north->img = ft_calloc(1, sizeof(t_ImageControl));
	cub->map->tex_south->img = ft_calloc(1, sizeof(t_ImageControl));
	cub->map->tex_west->img = ft_calloc(1, sizeof(t_ImageControl));
	cub->map->tex_east->img = ft_calloc(1, sizeof(t_ImageControl));
	if (is_xpm(cub, 1) || is_xpm(cub, 2)
		|| is_xpm(cub, 3) || is_xpm(cub, 4))
		return (1);
	if (check_access(cub))
		return (1);
	if (convert_textures(cub))
		return (1);
	return (0);
}
