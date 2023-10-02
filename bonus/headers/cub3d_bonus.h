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

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../../mlx/mlx.h"
# include "../../mlx/mlx_int.h"
# include "constants_bonus.h"
# include "libft.h"
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/time.h>
# include <stdlib.h>
# include <fcntl.h>

/**
 * @struct t_WindowConfig
 * Structure for configuring the window properties in the Cub3D project.
 * It defines the dimensions and aspect ratio of the game's rendering window.
 *
 * @param WindowSizeX Width of the rendering window in pixels.
 * @param WindowSizeY Height of the rendering window in pixels.
 * @param WindowAspectRatio Aspect ratio of the rendering window (Width /
 * Height).
 */
typedef struct s_WindowConfig
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
typedef struct s_ImageControl
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
 * @param img Pointer to the image control structure.
 */
typedef struct s_TextureSetup
{
	char			*path;
	t_ImageControl	*img;
}				t_TextureSetup;

/**
 * @struct t_PlayerConfig
 * Structure for managing player configuration and state in the game.
 *
 * This structure holds data related to the player's position, orientation,
 * input controls, and various gameplay attributes.
 *
 * @param orientation Player's orientation or facing direction.
 * @param pos_x X-coordinate of the player's position in 2D space.
 * @param pos_y Y-coordinate of the player's position in 2D space.
 * @param dir_x X-component of the player's facing direction vector.
 * @param dir_y Y-component of the player's facing direction vector.
 * @param up Flag indicating if the "up" movement control is active.
 * @param down Flag indicating if the "down" movement control is active.
 * @param left Flag indicating if the "left" movement control is active.
 * @param right Flag indicating if the "right" movement control is active.
 * @param l_key State of the left key or action.
 * @param r_key State of the right key or action.
 * @param shoot Flag indicating if the player is currently shooting.
 * @param use_distance_y Y-coordinate for use or interaction with objects.
 * @param use_distance_x X-coordinate for use or interaction with objects.
 * @param crosshair Pointer to the crosshair texture setup.
 * @param gun Pointer to the gun texture setup.
 */
typedef struct s_PlayerConfig
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
	int				l_key;
	int				r_key;
	int				shoot;
	float			use_distance_y;
	float			use_distance_x;
	t_TextureSetup	*crosshair;
	t_TextureSetup	*gun;
}				t_PlayerConfig;

/**
 * @struct t_MiniMap
 * Structure for managing the minimap in the Cub3D game.
 *
 * The minimap provides a scaled-down representation of the game world to
 * help players navigate and gain situational awareness.
 *
 * @param img Pointer to the image control structure for the minimap.
 * @param width Width of the minimap image.
 * @param height Height of the minimap image.
 * @param draw_x X-coordinate for drawing on the minimap image.
 * @param draw_y Y-coordinate for drawing on the minimap image.
 * @param player_x X-coordinate of the player's position on the minimap.
 * @param player_y Y-coordinate of the player's position on the minimap.
 * @param flag A flag used to determine the minimap's state or behavior.
 */
typedef struct s_MiniMap
{
	t_ImageControl	*img;
	int				width;
	int				height;
	int				draw_x;
	int				draw_y;
	int				player_x;
	int				player_y;
	int				flag;
}				t_MiniMap;

/**
 * @struct t_MapConfig
 * Structure for managing map configuration in the Cub3D game.
 *
 * The `t_MapConfig` structure holds various parameters and data related to the
 * game map, including file descriptors, map dimensions, matrix representation,
 * colors, and texture setups.
 *
 * @param fd File descriptor for the map file.
 * @param temp_fd Temporary file descriptor for map file operations.
 * @param n_lines Number of lines in the map.
 * @param max_line_len Maximum length of a line in the map.
 * @param skip_counter A counter used for parsing the map.
 * @param matrix Matrix representation of the map.
 * @param up_valid Flag indicating if up is valid in a given position.
 * @param down_valid Flag indicating if down is valid in a given position.
 * @param left_valid Flag indicating if left is valid in a given position.
 * @param right_valid Flag indicating if right is valid in a given position.
 * @param filename Name of the map file.
 * @param floor_c Color values for the floor.
 * @param ceilling_c Color values for the ceiling.
 * @param colors Flags indicating if floor and ceiling colors have been defined.
 * @param tex_north Texture setup for the north-facing wall.
 * @param tex_south Texture setup for the south-facing wall.
 * @param tex_east Texture setup for the east-facing wall.
 * @param tex_west Texture setup for the west-facing wall.
 * @param tex_door Texture setup for doors (if available, for bonus).
 * @param door_pos Positions of doors in the map (if available, for bonus).
 */
typedef struct s_MapConfig
{
	int				fd;
	int				temp_fd;
	int				n_lines;
	int				max_line_len;
	int				skip_counter;
	char			**matrix;
	int				up_valid;
	int				down_valid;
	int				left_valid;
	int				right_valid;
	char			*filename;
	int				floor_c[256][256][256];
	int				ceilling_c[256][256][256];
	bool			colors[2];
	t_TextureSetup	*tex_north;
	t_TextureSetup	*tex_south;
	t_TextureSetup	*tex_east;
	t_TextureSetup	*tex_west;
	t_TextureSetup	*tex_door;
	char			**door_pos;
}				t_MapConfig;

/**
 * @struct t_Transform
 * Structure for representing 3D transformations in space.
 *
 * The `t_Transform` structure holds three double precision values
 * (`x`, `y`, and `z`) representing 3D coordinates or transformations in space.
 *
 * @param x The x-coordinate or transformation value.
 * @param y The y-coordinate or transformation value.
 * @param z The z-coordinate or transformation value.
 */
typedef struct s_Transform
{
	double	x;
	double	y;
	double	z;
}				t_Transform;

/**
 * @struct t_CameraConfig
 * Structure for managing camera configuration in the Cub3D project.
 *
 * The `t_CameraConfig` structure holds various parameters and data related to
 * the camera used for rendering scenes in the Cub3D project.
 *
 * @param fov Field of view (FOV) angle in radians.
 * @param camera_x X-coordinate of the camera position.
 * @param plane_x X-coordinate of the camera's view plane.
 * @param plane_y Y-coordinate of the camera's view plane.
 * @param raydir_x X-coordinate of the current ray direction.
 * @param raydir_y Y-coordinate of the current ray direction.
 * @param olddir_x X-coordinate of the previous ray direction.
 * @param oldplane_x X-coordinate of the previous view plane.
 * @param map_x X-coordinate of the current map grid cell.
 * @param map_y Y-coordinate of the current map grid cell.
 * @param ddist_x Delta distance between X-coordinates of the current and next
 * map grid cells.
 * @param ddist_y Delta distance between Y-coordinates of the current and next
 * map grid cells.
 * @param s_dist_x Side distance to the next X-coordinate grid cell boundary.
 * @param s_dist_y Side distance to the next Y-coordinate grid cell boundary.
 * @param perp_wd Perpendicular wall distance from camera.
 * @param camera_rot Current camera rotation angle.
 * @param step_x Step value for X-coordinate in ray casting.
 * @param step_y Step value for Y-coordinate in ray casting.
 * @param hit Flag indicating if a wall has been hit.
 * @param side Flag indicating which side of the wall was hit (0 for vertical, 1
 * for horizontal).
 * @param line_height Height of the wall line to be drawn.
 * @param draw_start Starting pixel position for drawing the wall.
 * @param draw_end Ending pixel position for drawing the wall.
 * @param wall_dir Direction of the wall (North, South, East, or West).
 * @param wallhit Distance to the wall hit.
 * @param tex_x X-coordinate of the texture being sampled.
 * @param tex_y Y-coordinate of the texture being sampled.
 * @param tex_w Width of the currently selected texture.
 * @param tex_h Height of the currently selected texture.
 * @param tex_step Step size for texture sampling.
 * @param tex_pos Current texture sampling position.
 * @param tex Two-dimensional array representing wall textures.
 * @param tex_vector Flag indicating whether textures are being used.
 * @param color Color value for rendering.
 */
typedef struct s_CameraConfig
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
	bool			tex_vector;
	unsigned int	color;
}				t_CameraConfig;

/**
 * @struct t_Menu
 * Structure for managing the game menu in the Cub3D project.
 *
 * The `t_Menu` structure holds pointers to textures for the "Start"
 * and "Quit" buttons in the game menu.
 *
 * @param start Pointer to the texture setup for the "Start" button.
 * @param quit Pointer to the texture setup for the "Quit" button.
 */
typedef struct s_Menu
{
	t_TextureSetup	*start;
	t_TextureSetup	*quit;
}				t_Menu;

/**
 * @struct t_Cub3d
 * Main structure for managing the Cub3D game configuration.
 *
 * The `t_Cub3d` structure is the central configuration structure for the Cub3D
 * game.
 * It holds various components and flags for controlling the game's behavior.
 *
 * @param mlx_ptr Pointer to the MiniLibX connection.
 * @param win_ptr Pointer to the MiniLibX game window.
 * @param img_wall Pointer to an image representing walls.
 * @param img_floor Pointer to an image representing the floor.
 * @param mouse_x Current X-coordinate of the mouse cursor.
 * @param mouse_y Current Y-coordinate of the mouse cursor.
 * @param cam Pointer to the camera configuration structure.
 * @param player Pointer to the player configuration structure.
 * @param map Pointer to the map configuration structure.
 * @param img Pointer to the main game image control structure.
 * @param minimap Pointer to the minimap configuration structure.
 * @param main Pointer to the main menu configuration structure.
 * @param menu_active Flag indicating if the menu is currently active.
 * @param graphics_ok Flag indicating if graphics resources are initialized.
 * @param files_ok Flag indicating if game files are successfully loaded.
 * @param minimap_ok Flag indicating if the minimap is initialized.
 * @param cam_ok Flag indicating if the camera is configured.
 * @param menu_ok Flag indicating if the main menu is initialized.
 * @param gun_ok Flag indicating if the player's gun is set up.
 */
typedef struct s_Cub3d
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_wall;
	void			*img_floor;
	int				mouse_x;
	int				mouse_y;
	t_CameraConfig	*cam;
	t_PlayerConfig	*player;
	t_MapConfig		*map;
	t_ImageControl	*img;
	t_MiniMap		*minimap;
	t_Menu			*main;
	bool			menu_active;
	bool			graphics_ok;
	bool			files_ok;
	bool			minimap_ok;
	bool			cam_ok;
	bool			menu_ok;
	bool			gun_ok;
}				t_Cub3d;

// PROGRAM LIFECYCLE FUNCTIONS
// Section for functions managing program's start, execution, and termination.
void	free_main(t_Cub3d *cub);
void	free_textures(t_Cub3d *cub, t_TextureSetup *texture);
void	free_gun(t_Cub3d *cub);
void	free_cam(t_Cub3d *cub);
void	free_menu(t_Cub3d *cub);
int		gameloop(t_Cub3d *cub);

// MAP AND FILE PARSING FUNCTIONS
// Section for functions related to parsing map files and validating file types.
int		map_init(t_Cub3d *cub, char *file);
void	create_temp_map(t_Cub3d *cub, char *line);
int		check_map_validity(t_Cub3d *cub);
int		parse_map_file(t_Cub3d *cub);
int		is_valid_map_type(char *filename);
int		parse_elements(t_Cub3d *cub, int i, char *line);
void	get_map_n_lines(t_Cub3d *cub);
int		has_valid_info(t_Cub3d *cub);
int		has_valid_info2(t_Cub3d *cub, char *line);
int		has_valid_info3(t_Cub3d *cub, char *line);
int		set_tex_path(t_Cub3d *cub, char *path, int direction);
void	put_floor_ceil_color(t_Cub3d *cub, char *line, int n, int i);
int		fill_matrix(t_Cub3d *cub);
int		check_map_closed(t_Cub3d *cub);
int		check_surroundings(t_MapConfig *m, int i, int j);
int		check_surroundings_utils(t_MapConfig *m, int i, int j, char *charset);
int		get_matrix_borders(t_MapConfig *m, int i, int j);
int		check_walls_doors(t_MapConfig *m, int i, int j);
int		check_north_south(t_Cub3d *cub, char *line);
int		check_west_east(t_Cub3d *cub, char *line);
int		fill_bonus_info(t_Cub3d *cub, char *line);

// PLAYER MANAGEMENT FUNCTIONS
int		set_player_orientation(t_Cub3d *cub, char c);
int		player_gun(t_Cub3d *cub, t_PlayerConfig *p);
void	draw_gun(t_Cub3d *cub, t_PlayerConfig *p, int x, int y);
void	draw_crosshair(t_Cub3d *cub, t_PlayerConfig *p, int x, int y);

// FILE MANAGEMENT FUNCTIONS
// Section for managing file processes
void	ft_open(t_Cub3d *cub);
char	*skip_info(t_Cub3d *cub, char *line, int i);

// APPLICATION GRAPHICS FUNCTIONS
// Functions for managing graphics and window
int		boot(t_Cub3d *cub);
int		graphics(t_Cub3d *cub);
int		check_tex_validity(t_Cub3d *cub);
int		convert_textures(t_Cub3d *cub);
int		check_access(t_Cub3d *cub);
int		is_xpm(t_Cub3d *cub, int id);
void	my_mlx_pixel_put(t_ImageControl *img, int x, int y, int color);
void	load_xpm(t_Cub3d *c, t_ImageControl *i, char *file);

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
void	shoot_gun(t_Cub3d *cub, t_PlayerConfig *p, int *counter);
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
void	minimap_new_image(t_Cub3d *cub);
void	draw_static_player(t_Cub3d *cub);
void	draw_static_cube(t_Cub3d *cub, int type);
void	draw_static_map(t_Cub3d *cub);
void	draw_dynamic_player(t_Cub3d *cub);
void	draw_dynamic_cube(t_Cub3d *cub, int type);
void	draw_dynamic_map(t_Cub3d *cub, int temp_x, int temp_y);
int		max_x_array(t_Cub3d *cub);

// TEXTURE AND COLOR FUNCTIONS
void	render_ceilling_floor(t_Cub3d *cub);
int		*get_texture_addr(t_ImageControl *i);
void	apply_texture(t_Cub3d *cub, t_CameraConfig *c, int x, int id);
int		my_mlx_pixel_get(t_ImageControl *img, int x, int y);

// MAIN MENU
int		start_menu(t_Cub3d *cub);
void	setup_menu(t_Cub3d *cub, t_TextureSetup *tex, char *file);
int		button_mo(t_Cub3d *cub, t_ImageControl *i, char b);
void	update_button(t_Cub3d *c, t_ImageControl *i, int p, char b);

// MISCELLANEOUS UTILS
void	cub3d_new_image(t_Cub3d *cub);
void	restore_doors(t_Cub3d *cub, int x, int y, int i);
int		mouse_hook(int key, int x, int y, t_Cub3d *cub);
void	ft_clean_gnl(int fd, char *line);

#endif
