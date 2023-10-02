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

#include "../../headers/cub3d_bonus.h"

/**
 * @brief Load an XPM image as a texture.
 *
 * The `load_xpm` function loads an XPM image file and stores it as a texture in
 * the `t_ImageControl` structure. It sets the `width` and `height` properties
 * of the image and the `img_ptr` property to the loaded image pointer.
 *
 * @param c Pointer to the `t_Cub3d` structure containing program context and
 * data.
 * @param i Pointer to the `t_ImageControl` structure representing the image to
 * be loaded.
 * @param file The filename of the XPM image to be loaded.
 */
void	load_xpm(t_Cub3d *c, t_ImageControl *i, char *file)
{
	i->height = 0;
	i->width = 0;
	i->img_ptr = mlx_xpm_file_to_image(c->mlx_ptr, file, &i->width, &i->height);
	if (!i->img_ptr)
	{
		free_main(c);
		printf("Error: Failed loading %s texture", file);
		exit(EXIT_FAILURE);
	}
}

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
	int	fd[4 + BONUS];

	fd[0] = open(cub->map->tex_north->path, O_RDONLY);
	fd[1] = open(cub->map->tex_south->path, O_RDONLY);
	fd[2] = open(cub->map->tex_west->path, O_RDONLY);
	fd[3] = open(cub->map->tex_east->path, O_RDONLY);
	if (BONUS)
	{
		fd[4] = open(cub->map->tex_door->path, O_RDONLY);
		close(fd[4]);
		if (fd[4] < 0)
			return (1);
	}
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
	if (fd[2] != -1)
		close(fd[2]);
	if (fd[3] != -1)
		close(fd[3]);
	if (fd[0] < 0 || fd[1] < 0 || fd[2] < 0 || fd[3] < 0)
		return (1);
	return (0);
}

/**
 * @brief Convert and load textures for raycasting.
 *
 * The `convert_textures` function initializes the textures used for raycasting
 * in the `t_CameraConfig` structure. It loads XPM image files for north, south,
 * west, and east walls, converts them to integer arrays, and stores them in the
 * `tex` array. Additionally, it allocates memory for each texture and ensures
 * successful loading of the texture files.
 *
 * @param cub Pointer to the `t_Cub3d` structure containing program context and
 * data.
 * @return 0 if successful, 1 if there was an error in texture loading.
 */
int	convert_textures(t_Cub3d *cub)
{
	t_CameraConfig	*c;

	c = cub->cam;
	c->tex = ft_calloc(4 + BONUS, sizeof(int *));
	if (!cub->cam->tex)
		return (1);
	load_xpm(cub, cub->map->tex_north->img, cub->map->tex_north->path);
	load_xpm(cub, cub->map->tex_south->img, cub->map->tex_south->path);
	load_xpm(cub, cub->map->tex_west->img, cub->map->tex_west->path);
	load_xpm(cub, cub->map->tex_east->img, cub->map->tex_east->path);
	c->tex[0] = get_texture_addr(cub->map->tex_north->img);
	c->tex[1] = get_texture_addr(cub->map->tex_south->img);
	c->tex[2] = get_texture_addr(cub->map->tex_west->img);
	c->tex[3] = get_texture_addr(cub->map->tex_east->img);
	if (BONUS)
	{
		load_xpm(cub, cub->map->tex_door->img, cub->map->tex_door->path);
		c->tex[4] = get_texture_addr(cub->map->tex_door->img);
	}
	c->tex_vector = true;
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
	else if (id == 9)
		filename = ft_strdup(cub->map->tex_door->path);
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
	cub->cam->tex_vector = false;
	cub->map->tex_north->img = ft_calloc(1, sizeof(t_ImageControl));
	cub->map->tex_south->img = ft_calloc(1, sizeof(t_ImageControl));
	cub->map->tex_west->img = ft_calloc(1, sizeof(t_ImageControl));
	cub->map->tex_east->img = ft_calloc(1, sizeof(t_ImageControl));
	if (BONUS)
		cub->map->tex_door->img = ft_calloc(1, sizeof(t_ImageControl));
	if (is_xpm(cub, 1) || is_xpm(cub, 2)
		|| is_xpm(cub, 3) || is_xpm(cub, 4) || (BONUS && is_xpm(cub, 9)))
		return (1);
	if (check_access(cub))
		return (1);
	return (0);
}
