/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 20:00:53 by marvin            #+#    #+#             */
/*   Updated: 2023/08/25 20:00:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# define WINDOW_X 1920
# define WINDOW_Y 1080

# ifndef BONUS
#  define BONUS 0
# endif

# define SKIP 6 + BONUS

# define WHITE 0xFFFFFF
# define GREY 0x808080
# define RED 0xFF0000
# define YELLOW 0xFFFF00


# define UP 119
# define DOWN 115
# define LEFT 97
# define RIGHT 100
# define L_ARROW 65361
# define R_ARROW 65363
# define USE 101
# define ESC 65307

# define PI 0x3F
# define NO_DIR PI / 2
# define SO_DIR 3 * PI / 2
# define WE_DIR 0
# define EA_DIR PI
# define TEX_HEIGHT 64
# define TEX_WIDTH 64

# define DOOR_RANGE_X 10
# define DOOR_RANGE_Y 10

#endif
