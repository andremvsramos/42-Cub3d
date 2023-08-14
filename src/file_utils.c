/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:57:34 by andvieir          #+#    #+#             */
/*   Updated: 2023/08/14 18:04:16 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	ft_open(t_Cub3d *cub)
{
	cub->map->fd = open(cub->map->filename, O_RDONLY);
	if (cub->map->fd < 0)
	{
		free_main(cub);
		shutdown("Error: fatal: cannot open map file\n", true);
	}
}

char	*skip_info(t_Cub3d *cub, char *line)
{
	int	skip;
	int	i;

	skip = 0;
	while (skip < 6)
	{
		if(ft_strchr("\n", line[0]))
		{
			free(line);
			line = get_next_line(cub->map->fd);
		}
		if (!ft_strncmp("NO ", line, 3) || !ft_strncmp("SO ", line, 3)
			|| !ft_strncmp("WE ", line, 3) || !ft_strncmp("EA ", line, 3)
			|| !ft_strncmp("F ", line, 2) || !ft_strncmp("C ", line, 2))
			skip++;
		if (ft_strchr("1\t ", line[0]) && skip != 5)
			return (NULL);
		free(line);
		line = get_next_line(cub->map->fd);
	}
	while (ft_strchr("\n", line[0]))
	{
		free(line);
		line = get_next_line(cub->map->fd);
	}
	while (line)
	{
		i = 0;
		while (line[i])
		{
			if (!ft_strncmp("1", &line[i], 1))
			{
				puts(&line[i]);
				return (line);
			}
			i++;
		}
		free(line);
		line = get_next_line(cub->map->fd);
	}
	//CRIAR SKIP COUNTER NA ESTRUTUTRA PARA ALTERAR NAS VALID BOUNDARIES O VALOR DO INDEX,
	// NAO PODE SER 0
	return (line);
}
