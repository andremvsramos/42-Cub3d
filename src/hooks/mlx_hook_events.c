/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Untitled-1                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:28:03 by marvin            #+#    #+#             */
/*   Updated: 2023/08/19 19:28:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

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
	shutdown("Closing CUB3D\n", false);
	return (0);
}

/**
 * @brief Handle key events in the Cub3D application.
 *
 * The deal_key function is responsible for handling key events in the Cub3D
 * application. When a key is pressed, the function checks if the key code
 * matches the code for the 'Esc' key (65307). If the 'Esc' key is pressed,
 * the function calls the win_close function to close the game window and
 * perform necessary cleanup. The function returns 0 to indicate that the key
 * event has been handled.
 *
 * @param key The key code corresponding to the pressed key.
 * @param cub Pointer to the t_Cub3d structure containing program context and
 * data.
 * @return Returns 0 to indicate successful key event handling.
 */
int	deal_key(int key, t_Cub3d *cub)
{
	if (key == 65307)
		win_close(cub);
	return (0);
}

/**
 * @brief Set up event handlers and start the MiniLibX event loop.
 *
 * The `hook_events` function configures event handlers to manage user
 * interactions with the graphical window. It uses the `mlx_hook` function to
 * associate the `deal_key` function with keyboard events and the `win_close`
 * function with the window close event. Keyboard events are detected using
 * event code `2`, and the window close event is detected using event code
 * `17`. After setting up the event handlers, the function enters the MiniLibX
 * event loop using `mlx_loop`, allowing the program to respond to user inputs
 * and window events. The function returns 0 after the event loop completes.
 *
 * @param cub Pointer to the t_Cub3d structure containing program context and
 * data.
 * @return Always returns 0 to indicate successful event setup and execution.
 */
void	hook_events(t_Cub3d *cub)
{
	mlx_hook(cub->win->win_ptr, 2, 1L << 0, deal_key, cub);
	mlx_hook(cub->win->mlx_ptr, 17, 1L << 2, win_close, cub);
}
