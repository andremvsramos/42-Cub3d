#include "../../headers/cub3d.h"

void	draw_cube(t_Cub3d *cub, int type)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	cub->minimap->width = 10 * cub->map->max_line_len;
	cub->minimap->height = 10 * cub->map->n_lines;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			mlx_pixel_put(cub->mlx_ptr, cub->win_ptr,
					(cub->minimap->draw_x + j), (cub->minimap->draw_y + i), type);
			j++;
		}
		i++;
	}
}

void	draw_map(t_Cub3d *cub)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < cub->map->n_lines + 1)
	{
		x = 0;
		while (x < cub->map->max_line_len - 1)
		{
			if (cub->map->matrix[y][x] == '1')
				draw_cube(cub, BLACK);
			else
				draw_cube(cub, WHITE);
			cub->minimap->draw_x += 10;
			x++;
		}
		cub->minimap->draw_x = 30;
		cub->minimap->draw_y += 10;
		y++;
	}
}

void	init_minimap(t_Cub3d *cub)
{
	int	bpp;
	int	sl;
	int	end;

	cub->minimap = ft_calloc(1, sizeof(t_MiniMap));
	cub->minimap->img = ft_calloc(1, sizeof(t_ImageControl));
	cub->minimap->map_size = 12;
	cub->minimap->width = 400;
	cub->minimap->height = 400;
	cub->minimap->img->img_ptr = mlx_new_image(cub->mlx_ptr,
						cub->minimap->width, cub->minimap->height);
	cub->minimap->img->addr = mlx_get_data_addr(
			cub->minimap->img->img_ptr, &bpp, &sl, &end);
	cub->minimap->draw_x = 30;
	cub->minimap->draw_y = 30;
}

void	draw_minimap(t_Cub3d *cub)
{
	draw_map(cub);
}
