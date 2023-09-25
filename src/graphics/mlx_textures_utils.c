/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_textures_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:18:06 by andvieir          #+#    #+#             */
/*   Updated: 2023/09/25 09:43:32 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

/**
 * @brief Apply a shader effect to a given color.
 *
 * The `apply_shader` function takes an input color and applies a shader effect
 * based on the provided `id`. The shader effects modify the color's brightness.
 *
 * @param color The original color to which the shader effect will be applied.
 * @param id An identifier specifying the shader effect to apply:
 *        - `id == 1`: No shader effect is applied; the original color is
 *           returned.
 *        - `id == 2`: A darkening shader effect is applied (60% darkness).
 *        - `id == 3`: A stronger darkening shader effect is applied (40%
 *           darkness).
 *        - `id == 4`: No shader effect is applied; the original color is
 *           returned.
 * @return The modified color after applying the shader effect.
 */
int	apply_shader(int color, int id)
{
	float	d;
	int		r;
	int		g;
	int		b;

	if (id == 1 || id == 9)
		return (color);
	if (id == 2)
		d = 0.6;
	if (id == 3)
		d = 0.4;
	if (id == 4)
		d = 1;
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r *= d;
	g *= d;
	b *= d;
	color = (r << 16) | (g << 8) | b;
	return (color);
}

/**
 * @brief Retrieve the memory address of a texture's pixel data.
 *
 * The `get_texture_addr` function takes an `t_ImageControl` structure and
 * returns the memory address of the pixel data for the associated texture.
 * It allocates memory for a new integer array, copies the pixel data from the
 * texture, and returns the address of the new array.
 *
 * @param i Pointer to the `t_ImageControl` structure containing information
 *          about the texture.
 * @return The memory address of the pixel data for the texture.
 */
int	*get_texture_addr(t_ImageControl *i)
{
	int	*tmp;
	int	row_start;
	int	y;

	tmp = ft_calloc(i->height * i->width, sizeof(int));
	if (!tmp)
		return (NULL);
	i->addr = mlx_get_data_addr(i->img_ptr, &(i->bpp), &(i->len), &(i->endian));
	y = 0;
	while (y < i->height)
	{
		row_start = y * i->width;
		ft_memcpy(tmp + row_start, i->addr + row_start, i->width * sizeof(int));
		y++;
	}
	return (tmp);
}

/**
 * @brief Get the `t_ImageControl` structure associated with a texture ID.
 *
 * The `get_img_struct` function returns the `t_ImageControl` structure
 * associated with a specified texture ID from the `t_Cub3d` structure.
 *
 * @param cub Pointer to the `t_Cub3d` structure containing program context and
 * data.
 * @param id An identifier specifying which texture to retrieve.
 * @return A pointer to the `t_ImageControl` structure associated with the
 * specified texture ID.
 */
t_ImageControl *get_img_struct(t_Cub3d *cub, int id)
{
	if (id == 1)
		return (cub->map->tex_north->img);
	if (id == 2)
		return (cub->map->tex_south->img);
	if (id == 3)
		return (cub->map->tex_west->img);
	if (id == 4)
		return (cub->map->tex_east->img);
	if (id == 9)
		return (cub->map->tex_door->img);
	return (NULL);
}

/**
 * @brief Calculate the exact point of contact between the ray and the wall.
 *
 * The `get_wall_x` function calculates the `wall_x` value, which represents
 * the exact point of contact between the ray and the wall, in relation to the
 * player's position. It is used during the raycasting process.
 *
 * @param cub Pointer to the `t_Cub3d` structure containing program context and
 * data.
 * @param c Pointer to the `t_CameraConfig` structure containing camera
 * configuration data.
 * @return The `wall_x` value representing the point of contact with the wall.
 */
double get_wall_x(t_Cub3d *cub, t_CameraConfig *c)
{
	double	wall_x;

	if (!c->side)
	{
		wall_x = cub->player->pos_y + c->perp_wd * c->raydir_y;
		wall_x -= c->map_y;
	}
	else
	{
		wall_x = cub->player->pos_x + c->perp_wd * c->raydir_x;
		wall_x -= c->map_x;
	}
	return (wall_x);
}

/**
 * @brief Apply a texture to a wall and consider shader effects.
 *
 * The `apply_texture` function applies a texture to a wall at the specified
 * screen column `x` while taking into account the shader effect. It calculates
 * the texture coordinates, including `tx` and `ty`, based on the wall's
 * position and orientation. The function then iterates through the wall's
 * height and applies the texture to each pixel of the wall, considering the
 * texture offset and shader effect.
 *
 * @param cub Pointer to the `t_Cub3d` structure containing program context and
 * data.
 * @param c Pointer to the `t_CameraConfig` structure containing camera
 * configuration data.
 * @param x The current screen column being processed.
 * @param id An identifier specifying which texture to apply (e.g., north,
 * south, west, east).
 */
void	apply_texture(t_Cub3d *cub, t_CameraConfig *c, int x, int id)
{
	double	wall_x;
	double	tx;
	double	ty;
	int		y;
	t_ImageControl *img;

	img = get_img_struct(cub, id);
	wall_x =  get_wall_x(cub, c);
	tx = (int)(wall_x * (double)img->width);
	tx = img->width - tx - 1;
	c->tex_step = 1.0 * img->width / c->line_height;
	c->tex_pos = (c->draw_start - WINDOW_Y / 2 + c->line_height) * c->tex_step;
	y = c->draw_start;
	while (y++ < c->draw_end)
	{
		ty = ((int) c->tex_pos & ((img->height / 2) - 1));
		c->tex_pos += c->tex_step;
		if (x >= 0 && y >= 0 && tx >= 0 && ty >= 0)
		{
			c->color = my_mlx_pixel_get(img, tx, ty);
			c->color = apply_shader(c->color, c->wall_dir);
			my_mlx_pixel_put(cub->img, x, y, c->color);
		}
	}
}
