#include "../../headers/cub3d.h"

int	max_x_array(t_Cub3d *cub)
{
	int	y;
	int	x;
	int	most_x;

	y = 0;
	x = 0;
	most_x = 0;
	while(y < cub->map->n_lines + 1)
	{
		x = 0;
		while (cub->map->matrix[y][x])
			x++;
		if (x > most_x)
			most_x = x;
		y++;
	}
	return (most_x);
}
