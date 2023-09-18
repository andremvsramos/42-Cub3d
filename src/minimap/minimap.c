#include "../../headers/cub3d.h"

void	init_minimap(t_Cub3d *cub)
{
	int	bpp;
	int	sl;
	int	end;

	cub->minimap = ft_calloc(1, sizeof(t_MiniMap));
	cub->minimap->img = ft_calloc(1, sizeof(t_ImageControl));
	cub->minimap->map_size = 12;
	cub->minimap->width = 10 * cub->map->max_line_len;
	cub->minimap->height = 10 * cub->map->n_lines;
	cub->minimap->img->img_ptr = mlx_new_image(cub->mlx_ptr,
						cub->minimap->width, cub->minimap->height);
	cub->minimap->img->addr = mlx_get_data_addr(
			cub->minimap->img->img_ptr, &bpp, &sl, &end);
	cub->minimap->draw_x = 30;
	cub->minimap->draw_y = 30;
}

int	draw_minimap(t_Cub3d *cub)
{
	cub->minimap->draw_x = 30;
	cub->minimap->draw_y = 30;
	cub->minimap->player_x = cub->player->pos_x * 10;
	cub->minimap->player_y = cub->player->pos_y * 10;
	draw_map(cub);
	draw_player(cub);
	return (0);
}
