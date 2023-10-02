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

#include "../headers/cub3d_bonus.h"

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
 * @brief Handle interactions with the game menu.
 *
 * This function checks if the mouse cursor is over the "Start" and "Quit"
 * buttons, updates their appearance, and returns.
 *
 * @param cub Pointer to the main Cub3D game configuration.
 */
static void	menu_loop(t_Cub3d *cub)
{
	int	start;
	int	quit;

	start = button_mo(cub, cub->main->start->img, 's');
	quit = button_mo(cub, cub->main->quit->img, 'q');
	update_button(cub, cub->main->start->img, start, 's');
	update_button(cub, cub->main->quit->img, quit, 'q');
}

/**
 * @brief Main game loop responsible for game logic and rendering.
 *
 * The `gameloop` function is the core of the Cub3D game loop. It performs the
 * following actions:
 *
 * 1. If the game's menu is active (`cub->menu_active` is true), it calls the
 *    `menu_loop` function to handle menu interactions and updates.
 *
 * 2. If the menu is not active, it proceeds with the main game logic and
 * rendering:
 *    - Calls the `readmove` function to handle player movement.
 *    - Restores doors to their original state (if any) using the
 * 		`restore_doors`
 *      function. This function appears to take care of some game state
 * 		restoration.
 *    - Calls `cub3d_new_image` to create a new image for the main game window.
 *    - Calls `minimap_new_image` to create a new image for the minimap.
 *    - Draws the minimap using the `draw_minimap` function.
 *    - Executes raycasting and draws the game scene using the `draw_rays`
 * 		function.
 *    - Renders the player's gun using the `draw_gun` function.
 *    - Renders the crosshair using the `draw_crosshair` function.
 *    - Puts the main game image and minimap image to the game window using the
 *      `mlx_put_image_to_window` function.
 *    - Checks if the player is shooting (`cub->player->shoot`) and updates the
 *      gun animation using the `shoot_gun` function.
 *    - Deactivates the game menu (`cub->menu_active = false`) after rendering.
 *    - If the player is shooting, it increments the `gun` counter.
 *
 * @param cub Pointer to the main Cub3D game configuration structure.
 * @return Always returns 0.
 */
int	gameloop(t_Cub3d *cub)
{
	static int	gun;

	if (cub->menu_active)
	{
		menu_loop(cub);
		return (0);
	}
	readmove(cub, cub->player);
	restore_doors(cub, 0, 0, 0);
	cub3d_new_image(cub);
	minimap_new_image(cub);
	draw_minimap(cub);
	draw_rays(cub);
	draw_gun(cub, cub->player, 0, 0);
	draw_crosshair(cub, cub->player, 0, 0);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr,
		cub->img->img_ptr, 0, 0);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr,
		cub->minimap->img->img_ptr, 30, 30);
	if (cub->player->shoot)
		shoot_gun(cub, cub->player, &gun);
	cub->menu_active = false;
	if (cub->player->shoot)
		gun++;
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
	cub.files_ok = false;
	cub.menu_active = false;
	cub.minimap_ok = false;
	cub.menu_ok = false;
	cub.cam_ok = false;
	cub.gun_ok = false;
	initialization(ac, av, &cub);
	mlx_mouse_move(cub.mlx_ptr, cub.win_ptr, WINDOW_X / 2, WINDOW_Y / 2);
	mlx_mouse_get_pos(cub.mlx_ptr, cub.win_ptr, &cub.mouse_x, &cub.mouse_y);
	hook_events(&cub);
	mlx_loop_hook(cub.mlx_ptr, &gameloop, &cub);
	mlx_loop(cub.mlx_ptr);
	free_main(&cub);
	printf("Closing CUB3D\n");
	return (0);
}
