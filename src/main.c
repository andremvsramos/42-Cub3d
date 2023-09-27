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
 * @brief Handle the window closing event in the Cub3D application.
 *
 * The win_close function is responsible for handling the window closing event
 * within the Cub3D application. When triggered, it performs cleanup operations
 * by calling the free_main function to release allocated resources and ensure
 * a clean shutdown of the application. Additionally, it displays a message
 * indicating the closure of the application. The 'false' parameter passed to
 * the shutdown function indicates that the application should exit with a
 * successful status (EXIT_SUCCESS), preventing it from crashing due to errors.
 *
 * @param cub Pointer to the t_Cub3d structure containing program context
 * and data.
 */
int	win_close(t_Cub3d *cub)
{
	free_main(cub);
	printf("Closing CUB3D\n");
	exit(EXIT_SUCCESS);
}

/**
 * @brief Initialize the program and its components.
 *
 * The initialization function is responsible for setting up the initial
 * state of the program. It performs the following tasks:
 *
 * 1. Checks the number of command-line arguments and validates input.
 * 2. Initializes the map settings by parsing the provided map file.
 * 3. Attempts to initialize the graphics subsystem using MiniLibX.
 * 4. Handles errors and gracefully shuts down the program in case of failure.
 *
 * @param ac The number of command-line arguments.
 * @param av An array of strings representing the command-line arguments.
 * @param cub Pointer to the t_Cub3d structure that holds program data.
 */
static void	initialization(int ac, char **av, t_Cub3d *cub)
{
	if (ac != 2)
	{
		printf("Error: Please input exactly two arguments\n");
		exit(EXIT_FAILURE);
	}
	if (map_init(cub, av[1]))
	{
		free_main(cub);
		printf("Error: Failed initializing map settings\n");
		exit(EXIT_FAILURE);
	}
	if (boot(cub))
	{
		free_main(cub);
		printf("Error: Failed booting graphics.\n");
		printf("\tPlease check MiniLibX is installed on your system\n");
		printf("\tPlease check the texture files, so they are XPM\n");
		exit(EXIT_FAILURE);
	}
}

/**
 * @brief Main game loop for the Cub3D application.
 *
 * The `gameloop` function represents the core game loop of the Cub3D
 * application. It continuously checks for player movement using the `readmove`
 * function and updates the game state accordingly. After checking for player
 * movement, the function draws the rays in the scene using the `draw_rays`
 * function, which calculates and renders the scene based on the player's
 * perspective. Finally, it displays the rendered scene on the application
 * window using `mlx_put_image_to_window`.
 *
 * @param cub Pointer to the `t_Cub3d` structure containing program context and
 * data.
 * @return Always returns 0 as the game loop continues indefinitely until the
 * application exits.
 */
int	gameloop(t_Cub3d *cub)
{
	if (cub->menu_active)
	{
		int	start;
		int	quit;

		start = button_mo(cub, cub->main->start->img, 's');
		quit = button_mo(cub, cub->main->quit->img, 'q');
		update_button(cub, cub->main->start->img, start, 's');
		update_button(cub, cub->main->quit->img, quit, 'q');
		return (0);
	}
	readmove(cub, cub->player);
	restore_doors(cub);
	cub3d_new_image(cub);
	minimap_new_image(cub);
	/* mlx_destroy_image(cub->mlx_ptr, cub->player->gun_sprite->img->img_ptr);
	cub->player->gun_sprite->img->img_ptr = mlx_new_image(cub->mlx_ptr, 1280, 1181);
	cub->player->gun_sprite->img->addr = mlx_get_data_addr(cub->player->gun_sprite->img->img_ptr,
		&cub->player->gun_sprite->img->bpp, &cub->player->gun_sprite->img->len,
		&cub->player->gun_sprite->img->endian); */
	draw_rays(cub);
	//draw_gun(cub, cub->player, 0, 0);
	draw_minimap(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img->img_ptr, 0, 0);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr,
		cub->minimap->img->img_ptr, 30, 30);
	cub->menu_active = false;
   	return (0);
}

/**
 * Use mlx_mouse_hide(cub.mlx_ptr, cub.win_ptr) if you want
 * to hide the mouse.
 */
int	main(int ac, char **av, char **env)
{
	t_Cub3d	cub;

	(void)env;
	cub.graphics_ok = false;
	cub.menu_active = false;
	cub.framecount = 0;
	initialization(ac, av, &cub);
	mlx_mouse_move(cub.mlx_ptr, cub.win_ptr, WINDOW_X / 2, WINDOW_Y / 2);
	mlx_mouse_get_pos(cub.mlx_ptr, cub.win_ptr, &cub.mouse_x, &cub.mouse_y);
	//draw_rays(&cub);
	//draw_minimap(&cub);
	//mlx_put_image_to_window(cub.mlx_ptr, cub.win_ptr, cub.img->img_ptr, 0, 0);
	//mlx_put_image_to_window(cub.mlx_ptr, cub.win_ptr,
	//	cub.minimap->img->img_ptr, 30, 30);
	hook_events(&cub);
	mlx_loop_hook(cub.mlx_ptr, &gameloop, &cub);
	mlx_loop(cub.mlx_ptr);
	free_main(&cub);
	printf("Closing CUB3D\n");
	return (0);
}
