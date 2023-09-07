/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: programming-pc <programming-pc@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:54:18 by programming       #+#    #+#             */
/*   Updated: 2023/09/07 12:14:25 by programming      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

/* static void	draw_line(t_all *data, t_stk pos1, t_stk pos2, long color)
{
	double	delta_x;
	double	delta_y;
	double	step;
	int		coord;

	delta_x = pos2.x - pos1.x;
	delta_y = pos2.y - pos1.y;
	step = fabs(delta_y);
	if (fabs(delta_x) > fabs(delta_y))
		step = fabs(delta_x);
	delta_x /= step;
	delta_y /= step;
	while (fabs(pos2.x - pos1.x) > fabs(delta_x)
		|| fabs(pos2.y - pos1.y) > fabs(delta_y))
	{
		coord = floor(pos1.y) * floor(data->minimap.width) + floor(pos1.x);
		data->minimap.img.adr[coord] = color;
		pos1.x += delta_x;
		pos1.y += delta_y;
	}
} */

/* void	draw_lines(t_all *data)
{
	t_stk	pos1;
	t_stk	pos2;
	int		i;

	i = -1;
	pos1.y = 0;
	pos2.y = data->minimap.height;
	while (++i < data->map.x)
	{
		pos1.x = i * data->minimap.map_size;
		pos2.x = i * data->minimap.map_size;
		draw_line(data, pos1, pos2, GRAY);
	}
	i = -1;
	pos1.x = 0;
	pos2.x = data->minimap.width;
	while (++i < data->map.y)
	{
		pos1.y = i * data->minimap.map_size;
		pos2.y = i * data->minimap.map_size;
		draw_line(data, pos1, pos2, GRAY);
	}
} */

/* void	draw_player(t_all *data)
{
	int		i;
	t_stk	pos;
	t_stk	ray_pos;

	i = 0;
	pos.x = (ceil(data->pos_x) * data->minimap.map_size)
		- (data->minimap.map_size / 2);
	pos.y = (ceil(data->pos_y) * data->minimap.map_size)
		- (data->minimap.map_size / 2);
	while (i < data->win.x)
	{
		ray_pos.x = ceil(data->stk[i].x * data->minimap.map_size);
		ray_pos.y = ceil(data->stk[i].y * data->minimap.map_size);
		draw_line(data, pos, ray_pos, GREEN);
		i++;
	}
	draw_rectangle(data, (int)data->pos_x, (int)data->pos_y, RED);
} */
static void	init_minimap(t_Cub3d *cub)
{
	int	bpp;
	int	sl;
	int	end;

	cub->minimap = ft_calloc(1, sizeof(t_MiniMap));
	cub->minimap->img = ft_calloc(1, sizeof(t_ImageControl));
	cub->minimap->map_size = 16;
	cub->minimap->width = cub->map->max_line_len * cub->minimap->map_size;
	cub->minimap->height = cub->map->n_lines * cub->minimap->map_size;
	cub->minimap->img->img_ptr = mlx_new_image(cub->mlx_ptr,
						cub->minimap->width, cub->minimap->height);
	cub->minimap->img->addr = mlx_get_data_addr(
			cub->minimap->img->img_ptr, &bpp, &sl, &end);
}

static void	draw_rectangle(t_Cub3d *cub, int x, int y, long color)
{
	int	i;
	int	j;

	x *= cub->minimap->map_size;
	y *= cub->minimap->map_size;
	i = 0;
	while (i < cub->minimap->map_size)
	{
		j = 0;
		while (j < cub->minimap->map_size)
		{
			cub->minimap->img->addr[(y + i) * cub->map->max_line_len
				* cub->minimap->map_size + x + j] = color;
			j++;
		}
		i++;
	}
}

static void	draw_rectangles(t_Cub3d *cub)
{
	int		i;
	int		j;

	i = 0;
	while (i < cub->map->n_lines)
	{
		j = 0;
		while (cub->map->matrix[i][j])
		{
			if (cub->map->matrix[i][j] == '1')
				draw_rectangle(cub, j, i, WHITE);
			else
				draw_rectangle(cub, j, i, BLACK);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_Cub3d *cub)
{
	init_minimap(cub);
	draw_rectangles(cub);
}
