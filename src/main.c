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
	cub.frame1 = 0;
	cub.frame2 = 0;
	if (ac > 2)
		shutdown("Error: Run the program without extra arguments\n", true);
	else if (ac < 2)
		shutdown("Error: Please provide a map file\n", true);
	if (map_init(&cub, av[1]))
	{
		free_main(&cub);
		shutdown("Error: Failed initializing map settings\n", true);
	}
	if (player_init(cub))
	{
		free_main(&cub);
		shutdown("Error: Failed initializing player settings\n", true);
	}
	cub.graphics_ok = false;
	if (boot(&cub))
	{
		free_main(&cub);
		printf("Error: Failed booting graphics.\n");
		printf("\tPlease check MiniLibX is installed on your system\n");
		printf("\tPlease check the texture files, so they are XPM\n");
		shutdown("", true);
	}
	free_main(&cub);
	shutdown("Closing CUB3D\n", false);
}
