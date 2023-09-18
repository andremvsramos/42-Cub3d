#include "../../headers/cub3d.h"

void	draw_map(t_Cub3d *cub)
{
	int	x;
	int	y;

	while (y < cub->map->n_lines)
	{
		x = 0;
		while (x < cub->map->max_line_len)
		{
			if (cub->map->matrix[y][x] == '1')
				draw_cube(cub, 1);
			else
				draw_cube(cub, 0);
		}
		y++;
}

void	draw_player(t_Cub3d *cub)
{

}

void	draw_minimap(t_Cub3d *cub)
{

}
