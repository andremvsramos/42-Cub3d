/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Untitled-1                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:40:18 by marvin            #+#    #+#             */
/*   Updated: 2023/09/07 14:40:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

/**
 * @brief Check for wall collisions and update player position accordingly.
 *
 * The `check_wall_hit` function examines the player's potential new position
 * (specified by `temp_x` and `temp_y`) and checks if it collides with a wall in
 * the game map. If a collision is detected, the player's position is updated to
 * the specified coordinates, preventing the player from moving through walls.
 *
 * @param cub Pointer to the `t_Cub3d` structure containing program context and
 * data.
 * @param temp_x The temporary X-coordinate of the player's position.
 * @param temp_y The temporary Y-coordinate of the player's position.
 */
void	check_wall_hit(t_Cub3d *cub, double temp_x, double temp_y)
{
	t_MapConfig		*m;
	t_PlayerConfig	*p;

	m = cub->map;
	p = cub->player;
	if (m->matrix[(int)p->pos_y][(int)p->pos_x] == '1'
		|| m->matrix[(int)p->pos_y][(int)p->pos_x] == '9')
	{
		p->pos_y = temp_y;
		p->pos_x = temp_x;
	}
}

/**
 * @brief Apply forward or backward movement to the player.
 *
 * The `apply_for_back_move` function calculates the new player position when
 * moving forward or backward (specified by the `dir` parameter) along their
 * current direction. It updates the player's X and Y coordinates based on the
 * direction, direction vector, and a fixed movement distance. The function
 * then calls `check_wall_hit` to detect and handle collisions with walls.
 *
 * @param cub Pointer to the `t_Cub3d` structure containing program context
 * and data.
 * @param p   Pointer to the `t_PlayerConfig` structure containing player
 * configuration data.
 * @param dir The direction of movement (1 for forward, -1 for backward).
 */
void	apply_for_back_move(t_Cub3d *cub, t_PlayerConfig *p, int dir)
{
	double	temp_x;
	double	temp_y;

	temp_x = p->pos_x;
	temp_y = p->pos_y;
	p->pos_x += 0.2 * p->dir_x * dir;
	p->pos_y += 0.2 * p->dir_y * dir;
	check_wall_hit(cub, temp_x, temp_y);
}

/**
 * @brief Apply left or right strafing movement to the player.
 *
 * The `apply_left_right_move` function calculates the new player position when
 * strafing left or right (specified by the `dir` parameter) relative to their
 * current direction. It updates the player's X and Y coordinates based on the
 * direction, direction vector, and a fixed movement distance. The function then
 * calls `check_wall_hit` to detect and handle collisions with walls.
 *
 * @param cub Pointer to the `t_Cub3d` structure containing program context and
 * data.
 * @param p Pointer to the `t_PlayerConfig` structure containing player
 * configuration data.
 * @param dir The direction of strafing movement (1 for right, -1 for left).
 */
void	apply_left_right_move(t_Cub3d *cub, t_PlayerConfig *p, int dir)
{
	double	temp_x;
	double	temp_y;

	temp_x = p->pos_x;
	temp_y = p->pos_y;
	if (dir)
	{
		p->pos_x += p->dir_y * 0.2;
		p->pos_y += -p->dir_x * 0.2;
	}
	else
	{
		p->pos_x += -p->dir_y * 0.2;
		p->pos_y += p->dir_x * 0.2;
	}
	check_wall_hit(cub, temp_x, temp_y);
}

/**
 * @brief Handle player movement, both with keyboard input and mouse-based view
 * control.
 *
 * The `readmove` function manages player movement within the game world. It
 * checks the state of movement keys (up, down, left, right) and applies the
 * corresponding movement logic using the `apply_for_back_move` and
 * `apply_left_right_move` functions. These functions calculate the new player
 * position based on the direction and distance specified by the movement keys.
 * The `on_mouse_move` function is also called to handle mouse-based view
 * control. If any movement keys are pressed or if there is mouse movement, the
 * function returns 0 to indicate successful movement; otherwise, it returns 1
 * to indicate no movement.
 *
 * @param cub Pointer to the `t_Cub3d` structure containing program context and
 * data.
 * @param p Pointer to the `t_PlayerConfig` structure containing player
 * configuration data.
 * @return Returns 0 if the player's position is updated due to movement or view
 * control, or 1 if no movement keys are pressed and there is no mouse movement.
 */
int	readmove(t_Cub3d *cub, t_PlayerConfig *p)
{
	if (p->up)
		apply_for_back_move(cub, p, 1);
	if (p->down)
		apply_for_back_move(cub, p, -1);
	if (p->left)
		apply_left_right_move(cub, p, 1);
	if (p->right)
		apply_left_right_move(cub, p, 0);
	if (p->up || p->down || p->left || p->right || !on_mouse_move(cub))
		return (0);
	return (1);
}
