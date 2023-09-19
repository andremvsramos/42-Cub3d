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
# include <sys/types.h>
# include <sys/time.h>
# include <stdlib.h>
# include <fcntl.h>
# include <pthread.h>

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
	char			orientation;
	float			pos_x;
	float			pos_y;
	float			dir_x;
	float			dir_y;
	int				up;
	int				down;
	int				left;
	int				right;
	float			use_distance_y;
	float			use_distance_x;
	pthread_mutex_t	lock;
	pthread_cond_t	condition;
	bool			door_closed;
}				t_PlayerConfig;

typedef struct s_MiniMap
{
	t_ImageControl	*img;
	int				width;
	int				height;
	int				draw_x;
	int				draw_y;
	int				player_x;
	int				player_y;
	int				map_size;
}				t_MiniMap;

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
	int				floor_c[256][256][256];
	int				ceilling_c[256][256][256];
	bool			colors[2];
	t_TextureSetup	*tex_north;
	t_TextureSetup	*tex_south;
	t_TextureSetup	*tex_east;
	t_TextureSetup	*tex_west;
	t_TextureSetup	*tex_door;
}				t_MapConfig;


typedef struct	s_Transform
{
	double	x;
	double	y;
	double	z;
}				t_Transform;

typedef struct	s_CameraConfig
{
	double			fov;
	double			camera_x;
	double			plane_x;
	double			plane_y;
	double			raydir_x;
	double			raydir_y;
	double			olddir_x;
	double			oldplane_x;
	int				map_x;
	int				map_y;
	double			ddist_x;
	double			ddist_y;
	double			s_dist_x;
	double			s_dist_y;
	double			perp_wd;
	double			camera_rot;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				wall_dir;
	float			wallhit;
	int				tex_x;
	int				tex_y;
	int				tex_w;
	int				tex_h;
	float			tex_step;
	float			tex_pos;
	int				**tex;
	unsigned int	color;
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
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_wall;
	void			*img_floor;
	bool			graphics_ok;
	double			time;
	double			oldtime;
	double			fps;
	int				mouse_x;
	int				mouse_y;
	t_CameraConfig	*cam;
	t_PlayerConfig	*player;
	t_MapConfig		*map;
	t_ImageControl	*img;
	t_MiniMap		*minimap;

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
void	my_mlx_pixel_put(t_ImageControl *img, int x, int y, int color);

// EVENT HANDLING FUNCTIONS
// Functions related to handling user input events
void	hook_events(t_Cub3d *cub);
int		deal_key(int key, t_Cub3d *cub);
int		on_mouse_move(t_Cub3d *cub);
int		win_close(t_Cub3d *cub);

// PLAYER HANDLING FUNCTIONS
// Functions related to handling player events
int		player_init(t_Cub3d *cub);
void	set_player_position(t_Cub3d *cub);
int		use_action(t_PlayerConfig *p, t_MapConfig *m);
int		readmove(t_Cub3d *cub, t_PlayerConfig *p);
void	apply_for_back_move(t_Cub3d *cub, t_PlayerConfig *p, int dir);
void	apply_left_right_move(t_Cub3d *cub, t_PlayerConfig *p, int dir);
void	check_wall_hit(t_Cub3d *cub, double temp_x, double temp_y);


// CAMERA HANDLING FUNCTIONS
// Functions related to handling camera events
int		camera_init(t_Cub3d *cub);
void	cam_utils_init(t_CameraConfig *cam);

// RAYCASTING FUNCTIONS
void	draw_rays(t_Cub3d *cub);
void	ray_per_colum(t_Cub3d *cub, t_CameraConfig *cam, int x);
void	ray_map_pos(t_Cub3d *cub, t_CameraConfig *cam);
void	ray_delt_dist(t_CameraConfig *cam);
void	step_calculation(t_CameraConfig *cam, t_PlayerConfig *p);
void	apply_dda(t_CameraConfig *cam, t_MapConfig *m);
void	calculate_wall_height(t_CameraConfig *cam);
void	get_wall_direction(t_MapConfig *m, t_CameraConfig *c);

// MINIMAP FUNCTIONS
//Functions related to minimap drawing
int		draw_minimap(t_Cub3d *cub);
void	init_minimap(t_Cub3d *cub);
void	draw_player(t_Cub3d *cub);
void	draw_cube(t_Cub3d *cub, int type);
void	draw_map(t_Cub3d *cub);

// TEXTURE AND COLOR FUNCTIONS
void	render_ceilling_floor(t_Cub3d *cub);
int		*get_texture_addr(t_ImageControl *i);
void	apply_texture(t_Cub3d *cub, t_CameraConfig *c, int x, int id);
int		my_mlx_pixel_get(t_ImageControl *img, int x, int y);

// MISCELLANEOUS UTILS
void	ft_wait(unsigned long long ms);

#endif
