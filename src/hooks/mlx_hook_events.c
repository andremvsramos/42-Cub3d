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
 * @brief Handle the key press event to initiate player movement.
 *
 * The `move_press` function is called when a key press event is detected. It
 * checks the key code and sets the corresponding player movement flag to
 * indicate the direction of movement. This function is primarily used for
 * initiating player movement when keys like UP, DOWN, LEFT, or RIGHT are
 * pressed.
 *
 * @param key The key code of the pressed key.
 * @param cub Pointer to the `t_Cub3d` structure containing program context and
 * data.
 * @return Returns 0 after setting the player movement flag, or 1 if an invalid
 * key code is provided.
 */
int	move_press(int key, t_Cub3d *cub)
{
	if (key == UP)
		return (cub->player->up = 1, 0);
	else if (key == DOWN)
		return (cub->player->down = 1, 0);
	else if (key == LEFT)
		return (cub->player->left = 1, 0);
	else if (key == RIGHT)
		return (cub->player->right = 1, 0);
	return (1);
}

/**
 * @brief Handle the key release event to stop player movement.
 *
 * The `move_release` function is called when a key release event is detected.
 * It checks the key code and clears the corresponding player movement flag to
 * indicate that the movement in that direction should stop. This function is
 * primarily used for stopping player movement when keys like UP, DOWN, LEFT,
 * or RIGHT are released.
 *
 * @param key The key code of the released key.
 * @param cub Pointer to the `t_Cub3d` structure containing program context and
 * data.
 * @return Returns 0 after clearing the player movement flag, or 1 if an invalid
 * key code is provided.
 */
int	move_release(int key, t_Cub3d *cub)
{
	if (key == UP)
		return (cub->player->up = 0, 0);
	else if (key == DOWN)
		return (cub->player->down = 0, 0);
	else if (key == LEFT)
		return (cub->player->left = 0, 0);
	else if (key == RIGHT)
		return (cub->player->right = 0, 0);
	return (0);
}

/**
 * @brief Handle key press events, including game actions and player movement.
 *
 * The `on_key_press` function is responsible for processing key press events.
 * It checks the key code and performs corresponding actions such as closing the
 * window when the ESC key is pressed. Additionally, it invokes the `move_press`
 * function to handle player movement based on the pressed keys.
 *
 * @param key The key code of the pressed key.
 * @param cub Pointer to the `t_Cub3d` structure containing program context and
 * data.
 * @return Returns 0 after processing the key press event, or 1 if an invalid
 * key code is provided.
 */
int	on_key_press(int key, t_Cub3d *cub)
{
	puts(ft_itoa(key));
	if (key == ESC)
		win_close(cub);
	move_press(key, cub);
	if (key == USE)
		use_action(cub->player, cub->map);
	return (0);
}

/**
 * @brief Handle key release events, including stopping player movement.
 *
 * The `on_key_release` function is responsible for processing key release
 * events. It checks the key code and performs corresponding actions such as
 * closing the window when the ESC key is released. Additionally, it invokes
 * the `move_release` function to stop player movement based on the released
 * keys.
 *
 * @param key The key code of the released key.
 * @param cub Pointer to the `t_Cub3d` structure containing program context and
 * data.
 * @return Returns 0 after processing the key release event, or 1 if an invalid
 * key code is provided.
 */
int	on_key_release(int key, t_Cub3d *cub)
{
	if (key == ESC)
		win_close(cub);
	if (move_release(key, cub))
		return (0);
	return (0);
}

/**
 * @brief Register event hooks for keyboard inputs and window closing.
 *
 * The `hook_events` function is responsible for registering event hooks for
 * keyboard inputs (both key press and key release) and window closing. It uses
 * the MiniLibX functions `mlx_hook` to set up event handling. Keyboard input
 * events are directed to the `on_key_press` and `on_key_release` functions,
 * while window closing events are handled by the `win_close` function.
 *
 * @param cub Pointer to the `t_Cub3d` structure containing program context and
 * data.
 */
void	hook_events(t_Cub3d *cub)
{
	mlx_hook(cub->win_ptr, DestroyNotify, NoEventMask, win_close, cub);
	mlx_hook(cub->win_ptr, KeyPress, KeyPressMask, on_key_press, cub);
	mlx_hook(cub->win_ptr, KeyRelease, KeyReleaseMask, on_key_release, cub);
}
