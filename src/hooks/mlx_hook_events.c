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

int	deal_key(int key, t_Cub3d *cub)
{
	if (key == 65307)
		win_close(cub);
	return (0);
}

/**
 * @brief Set up event hooks for handling user interactions in the Cub3D
 * application.
 *
 * The hook_events function is responsible for setting up event hooks to capture
 * user interactions within the Cub3D application. It uses the mlx_hook function
 * to associate event types with their corresponding event handlers. The
 * KeyPress event is associated with the deal_key function, which handles
 * keyboard input events. Additionally, the DestroyNotify event, triggered when
 * the window is closed, is associated with the win_close function to handle
 * proper cleanup.
 *
 * @param cub Pointer to the t_Cub3d structure containing program context and data.
 */
int	hook_events(t_Cub3d *cub)
{
	mlx_hook(cub->win_ptr, 2, 1L << 0, deal_key, cub);
	mlx_hook(cub->mlx_ptr,17, 1L << 0, win_close, cub);
	mlx_loop(cub->mlx_ptr);
	return (0);
}
