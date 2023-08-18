/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:20:16 by andvieir          #+#    #+#             */
/*   Updated: 2023/08/10 15:20:16 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "libft.h"
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>

# ifndef WINDOW_X
#  define WINDOW_X 1024
# endif

# ifndef WINDOW_Y
#  define WINDOW_Y 768
# endif

/**
 * @struct t_WindowConfig
 * Structure for configuring the window properties in the Cub3D project.
 * It defines the dimensions and aspect ratio of the game's rendering window.
 *
 * @param WindowSizeX Width of the rendering window in pixels.
 * @param WindowSizeY Height of the rendering window in pixels.
 * @param WindowAspectRatio Aspect ratio of the rendering window (Width / Height).
 */
typedef struct	s_WindowConfig
{
	int	width;
	int	height;
	int	aspect_ratio;
}				t_WindowConfig;

/**
 * @struct t_ImageControl
 * Structure for managing image data and properties in the Cub3D project.
 * It provides control over various image-related attributes for rendering.
 *
 * @param img_ptr A pointer to the image's pixel data.
 * @param addr A char pointer to the start of the image's pixel data.
 * @param bpp Bits per pixel for the image.
 * @param len Length of each image line in bytes.
 * @param endian The byte order in the image data (endianess).
 */
typedef struct	s_ImageControl
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
}				t_ImageControl;

typedef struct	s_TextureSetup
{
	char	*path_north;
	char	*path_south;
	char	*path_west;
	char	*path_east;
	int		floor_c[255][255][255];
	int		ceilling_c[255][255][255];
	bool	colors[2];
}				t_TextureSetup;

typedef struct	s_PlayerConfig
{
	char	orientation;
	int		player_x;
	int		player_y;
}				t_PlayerConfig;

/**
 * @struct t_MapConfig
 * A structure representing the configuration and data of the game map.
 *
 * @param fd The file descriptor associated with the map file.
 * @param n_lines The number of lines in the map.
 * @param filename The name of the map file being processed.
 */
typedef struct	s_MapConfig
{
	int				fd;
	int				temp_fd;
	int				n_lines;
	int				max_line_len;
	int				skip_counter;
	char			**matrix;
	char			*filename;
	t_TextureSetup	*tex;
	t_PlayerConfig	*player;
}				t_MapConfig;


/**
 * @struct t_Cub3d
 * The main structure representing the context and data for the Cub3D project.
 * It holds essential information related to the game's execution and rendering.
 *
 * @param filename The name of the scene description file being processed.
 * @param mlx_ptr A pointer to the MinilibX context for graphics operations.
 * @param win_ptr A pointer to the game's main window created with MinilibX.
 * @param img A pointer to an image control structure for managing graphical data.
 * @param map A pointer to the structure holding map configuration and data.
 */
typedef struct	s_Cub3d
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_ImageControl	*img;
	t_MapConfig		*map;

}				t_Cub3d;


// PROGRAM LIFECYCLE FUNCTIONS
// Section for functions managing program's start, execution, and termination.
void	shutdown(char *str, bool crash);
void	free_main(t_Cub3d *cub);

// MAP AND FILE PARSING FUNCTIONS
// Section for functions related to parsing map files and validating file types.
void	map_init(t_Cub3d *cub, char *file);
void	create_temp_map(t_Cub3d *cub, char *line);
int		check_map_validity(t_Cub3d *cub);
int		parse_map_file(t_Cub3d *cub);
int		is_valid_map_type(char *filename);
int		parse_elements(t_Cub3d *cub, int i);
void	get_map_n_lines(t_Cub3d *cub, int i);
int		has_valid_info(t_Cub3d *cub);
void	put_floor_ceil_color(t_Cub3d *cub, char *line, int n, int i);
int		fill_matrix(t_Cub3d *cub);
int		check_map_closed(t_Cub3d *cub);

// PLAYER MANAGEMENT FUNCTIONS
int	set_player_orientation(t_Cub3d *cub, char c);

// FILE MANAGEMENT FUNCTIONS
// Section for managing file processes
void	ft_open(t_Cub3d *cub);
char	*skip_info(t_Cub3d *cub, char *line);

#endif
