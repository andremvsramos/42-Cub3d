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
# include "../mlx/mlx_int.h"
# include "constants.h"
# include "libft.h"
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>

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
	void	*mlx_ptr;
	void	*win_ptr;
	int		width;
	int		height;
	int		aspect_ratio;
}				t_WindowConfig;

/**
 * @struct t_ImageControl
 * @brief Structure for managing image data and properties in the Cub3D
 * project.
 *
 * The t_ImageControl structure provides control over various image-related
 * attributes required for rendering in the Cub3D project.
 *
 * @param img_ptr A pointer to the image's pixel data.
 * @param addr A char pointer to the start of the image's pixel data.
 * @param bpp Bits per pixel for the image.
 * @param len Length of each image line in bytes.
 * @param endian The byte order in the image data (endianess).
 * @param width Width of the image in pixels.
 * @param height Height of the image in pixels.
 */
typedef struct	s_ImageControl
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
	int		width;
	int		height;

}				t_ImageControl;

/**
 * @struct t_TextureSetup
 * Structure for managing texture setup in the Cub3D project.
 *
 * This structure holds data related to texture paths and images.
 *
 * @param path Path to the texture file.
 * @param xpm MiniLibX pointer to the texture image.
 * @param img Pointer to the image control structure.
 */
typedef struct	s_TextureSetup
{
	char			*path;
	void			*xpm;
	t_ImageControl	*img;
}				t_TextureSetup;

/**
 * @struct t_PlayerConfig
 * @brief Structure for managing player configuration in the Cub3D map.
 *
 * This structure holds data related to the player's position and orientation.
 *
 * @param orientation Orientation of the player (e.g., 'N' for north).
 * @param pos_x X-coordinate of the player's position.
 * @param pos_y Y-coordinate of the player's position.
 */
typedef struct	s_PlayerConfig
{
	char	orientation;
	int		pos_x;
	int		pos_y;
	double	dir_x;
	double	dir_y;
	double	fov_x;
	double	fov_y;
}				t_PlayerConfig;

/**
 * @struct t_MapConfig
 * Structure for managing map configuration and data in the Cub3D project.
 *
 * This structure holds information about the map layout, textures,
 * and player data.
 *
 * @param fd File descriptor for the map file.
 * @param temp_fd Temporary file descriptor for parsing.
 * @param n_lines Number of lines in the map file.
 * @param max_line_len Maximum length of lines in the map.
 * @param skip_counter Counter for skipped lines in the map.
 * @param matrix A matrix representing the map layout.
 * @param filename Name of the map file.
 * @param floor_c Colors for floor tiles.
 * @param ceilling_c Colors for ceiling tiles.
 * @param colors Array indicating color presence.
 * @param tex_north Texture setup for the north side.
 * @param tex_south Texture setup for the south side.
 * @param tex_east Texture setup for the east side.
 * @param tex_west Texture setup for the west side.
 * @param player Player configuration in the map.
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
	int				floor_c[255][255][255];
	int				ceilling_c[255][255][255];
	bool			colors[2];
	t_TextureSetup	*tex_north;
	t_TextureSetup	*tex_south;
	t_TextureSetup	*tex_east;
	t_TextureSetup	*tex_west;
}				t_MapConfig;

typedef struct	s_CameraConfig
{
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
}				t_CameraConfig;


/**
 * @struct t_Cub3d
 * @brief The main structure representing the context and data for the Cub3D
 * project.
 *
 * This structure holds essential information related to the game's execution
 * and rendering.
 *
 * @param mlx_ptr A pointer to the MinilibX context for graphics operations.
 * @param win_ptr A pointer to the game's main window created with MinilibX.
 * @param graphics_ok Flag indicating successful graphics context setup.
 * @param frame1 Timestamp of the previous frame for frame rate calculation.
 * @param frame2 Timestamp of the current frame for frame rate calculation.
 * @param fps Calculated frames per second.
 * @param player A pointer to the structure holding player configuration.
 * @param map A pointer to the structure holding map configuration and data.
 * @param img A pointer to an image control structure for managing graphical
 * data.
 */
typedef struct	s_Cub3d
{
	bool			graphics_ok;
	double			frame1;
	double			frame2;
	double			fps;
	t_CameraConfig	*cam;
	t_PlayerConfig	*player;
	t_MapConfig		*map;
	t_ImageControl	*img;
	t_WindowConfig	*win;

}				t_Cub3d;


// PROGRAM LIFECYCLE FUNCTIONS
// Section for functions managing program's start, execution, and termination.
void	shutdown(char *str, bool crash);
void	free_main(t_Cub3d *cub);
int		gameloop(t_Cub3d *cub);

// MAP AND FILE PARSING FUNCTIONS
// Section for functions related to parsing map files and validating file types.
int		map_init(t_Cub3d *cub, char *file);
void	create_temp_map(t_Cub3d *cub, char *line);
int		check_map_validity(t_Cub3d *cub);
int		parse_map_file(t_Cub3d *cub);
int		is_valid_map_type(char *filename);
int		parse_elements(t_Cub3d *cub, int i);
void	get_map_n_lines(t_Cub3d *cub);
int		has_valid_info(t_Cub3d *cub);
void	put_floor_ceil_color(t_Cub3d *cub, char *line, int n, int i);
int		fill_matrix(t_Cub3d *cub);
int		check_map_closed(t_Cub3d *cub);

// PLAYER MANAGEMENT FUNCTIONS
int		set_player_orientation(t_Cub3d *cub, char c);

// FILE MANAGEMENT FUNCTIONS
// Section for managing file processes
void	ft_open(t_Cub3d *cub);
char	*skip_info(t_Cub3d *cub, char *line);

// APPLICATION GRAPHICS FUNCTIONS
// Functions for managing graphics and window
int		boot(t_Cub3d *cub);
int		graphics(t_Cub3d *cub);
int		check_tex_validity(t_Cub3d *cub);
int		is_xpm(t_Cub3d *cub, int id);

// EVENT HANDLING FUNCTIONS
// Functions related to handling user input events
void	hook_events(t_Cub3d *cub);
int		deal_key(int key, t_Cub3d *cub);
int		win_close(t_Cub3d *cub);

// PLAYER HANDLING FUNCTIONS
// Functions related to handling player events
int		player_init(t_Cub3d *cub);
void	set_player_position(t_Cub3d *cub);

// CAMERA HANDLING FUNCTIONS
// Functions related to handling camera events
int		camera_init(t_Cub3d *cub);
void	raycast_init(t_Cub3d *cub);

#endif
