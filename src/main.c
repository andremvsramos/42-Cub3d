/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:27:24 by andvieir          #+#    #+#             */
/*   Updated: 2023/08/10 15:27:24 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

/**
 * @brief Gracefully terminate the program with optional error message.
 *
 * This function is responsible for controlled program termination.
 * It takes a null-terminated string `str` as an argument and writes its
 * characters to the standard error output.
 * If the `crash` flag is true, the function exits the program with a failure
 * status; if false, it exits with a success status.
 *
 * @param str Null-terminated string containing an error message (can be NULL).
 * @param crash If true, the program exits with a failure status;
 * if false, with a success status.
 */
void	shutdown(char *str, bool crash)
{
	while (*str)
		write(STDERR_FILENO, str++, 1);
	if (crash)
		exit(EXIT_FAILURE);
	else
		exit(EXIT_SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	t_Cub3d	cub;

	(void)env;
	if (ac > 2)
		shutdown("Error: Run the program without extra arguments\n", true);
	else if (ac < 2)
		shutdown("Error: Please provide a map file\n", true);
	cub.map = ft_calloc(1, sizeof(t_MapConfig));
	cub.map->skip_counter = 0;
	//cub.img = ft_calloc(1, sizeof(t_ImageControl));
	cub.map->filename = ft_strdup(av[1]);
	cub.map->tex = ft_calloc(1, sizeof(t_TextureSetup));
	cub.map->tex->colors[0] = false;
	cub.map->tex->colors[1] = false;
	parse_map_file(&cub);
}
