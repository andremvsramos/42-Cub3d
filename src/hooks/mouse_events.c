/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 23:28:18 by marvin            #+#    #+#             */
/*   Updated: 2023/09/14 23:28:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

/**
 * @brief Rotate the player's view and camera direction based on a given angle.
 *
 * The `rotate_player` function calculates the new direction of the player
 * and the camera plane after applying the rotation specified by the `angle`
 * parameter. It updates the player's direction and the camera plane in the
 * game context (`cub`) accordingly.
 *
 * @param cub   Pointer to the `t_Cub3d` structure containing program context
 * and data.
 * @param angle The angle by which to rotate the player's view.
 */
static void	rotate_player(t_Cub3d *cub, double angle)
{
	t_PlayerConfig	*p;
	t_CameraConfig	*c;
	t_Transform		rot_dir;
	t_Transform		rot_plane;

	c = cub->cam;
	p = cub->player;
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
 * @brief Handle mouse movement events and update the player's view.
 *
 * The `on_mouse_move` function calculates the speed and direction of mouse
 * movement, and if there is movement detected, it calls `rotate_player` to
 * adjust the player's view based on the mouse movement speed. It helps
 * implement smooth and responsive mouse-based view control in the game.
 *
 * @param cub Pointer to the `t_Cub3d` structure containing program context
 * and data.
 * @return Returns 0 if there is mouse movement and the player's view is
 * updated, or 1 if there is no mouse movement.
 */
int	on_mouse_move(t_Cub3d *cub)
{
	int		temp_x;
	int		mouse_x_diff;
	double	rot_speed;

	temp_x = cub->mouse_x;
	mlx_mouse_get_pos(cub->mlx_ptr, cub->win_ptr, &cub->mouse_x, &cub->mouse_y);
	//puts(ft_itoa(cub->mouse_x));
	mouse_x_diff = cub->mouse_x - temp_x;
	if (mouse_x_diff)
	{
		rot_speed = 0.002 * mouse_x_diff;
		rotate_player(cub, rot_speed);
		return (0);
	}
	return (1);
}