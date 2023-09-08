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

void	rotate_player(t_Cub3d *cub, int dir)
{
	t_PlayerConfig	*p;
	t_CameraConfig	*c;
	t_Transform		rot_dir;
	t_Transform		rot_plane;
	double			angle;

	c = cub->cam;
	p = cub->player;
	if (dir)
		angle = 0.0349;
	else
		angle = -0.0349;
	rot_dir.x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
	rot_dir.y = p->dir_x * sin(angle) + p->dir_y * cos(angle);
	p->dir_x = rot_dir.x;
	p->dir_y = rot_dir.y;
	rot_plane.x = c->plane_x * cos(angle) - c->plane_y * sin(angle);
	rot_plane.y = c->plane_x * sin(angle) + c->plane_y * cos(angle);
	c->plane_x = rot_plane.x;
	c->plane_y = rot_plane.y;
}

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
	t_MapConfig *m;
	t_PlayerConfig *p;

	m = cub->map;
	p = cub->player;
	if (m->matrix[(int)p->pos_y][(int)p->pos_x] == '1')
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
 * direction, direction vector, and a fixed movement distance. The function then
 * calls `check_wall_hit` to detect and handle collisions with walls.
 *
 * @param cub Pointer to the `t_Cub3d` structure containing program context and
 * data.
 * @param p Pointer to the `t_PlayerConfig` structure containing player
 * configuration data.
 * @param dir The direction of movement (1 for forward, -1 for backward).
 */
void	apply_for_back_move(t_Cub3d *cub, t_PlayerConfig *p, int dir)
{
	puts("forback");
	double	temp_x;
	double	temp_y;
	int		signal;

	temp_x = p->pos_x;
	temp_y = p->pos_y;
	if (dir)
		signal = 1;
	else
		signal = -1;
	p->pos_x = p->pos_x + (signal) * p->dir_x * 0.035;
	p->pos_y = p->pos_y + (signal) * p->dir_y * 0.035;
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
	puts("leftrigt");

	double	temp_x;
	double	temp_y;

	temp_x = p->pos_x;
	temp_y = p->pos_y;
	if (dir)
	{
		//p->pos_x += p->dir_y * 0.035;
		//p->pos_y += -p->dir_x * 0.035;
		rotate_player(cub, 0);
	}
	else
	{
		//p->pos_x += -p->dir_y * 0.035;
		//p->pos_y += p->dir_x * 0.035;
		rotate_player(cub, 1);
	}
	check_wall_hit(cub, temp_x, temp_y);
}

/**
 * @brief Handle player movement and collision detection.
 *
 * The `readmove` function manages player movement within the game world. It
 * checks the state of movement keys (up, down, left, right) and applies the
 * corresponding movement logic using the `apply_for_back_move` and
 * `apply_left_right_move` functions. These functions calculate the new player
 * position based on the direction and distance specified by the movement keys
 * and perform collision detection using the `check_wall_hit` function. If any
 * movement keys are pressed, the function returns 0 to indicate successful
 * movement; otherwise, it returns 1 to indicate no movement.
 *
 * @param cub Pointer to the `t_Cub3d` structure containing program context and
 * data.
 * @param p Pointer to the `t_PlayerConfig` structure containing player
 * configuration data.
 * @return Returns 0 if the player's position is updated due to movement, or 1
 * if no movement keys are pressed.
 */
int	readmove(t_Cub3d *cub, t_PlayerConfig *p)
{
	printf("PX : %d | PY : %d | DIRX: %f | DIRY: %f\n", cub->player->pos_x, cub->player->pos_y, cub->player->dir_x, cub->player->dir_y);
	if (p->up)
		apply_for_back_move(cub, p, 1);
	if (p->down)
		apply_for_back_move(cub, p, 0);
	if (p->left)
		apply_left_right_move(cub, p, 1);
	if (p->right)
		apply_left_right_move(cub, p, 0);
	if (p->up || p->down || p->left || p->right)
		return (0);
	return (1);
}
