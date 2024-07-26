/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:58:37 by rdias-ba          #+#    #+#             */
/*   Updated: 2024/07/26 08:15:42 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include "mlx.h"
# include <math.h>

/*---------------MESSAGES----------------*/

# define ERR_ARGS 		"Wrong arguments: Use ./cub3D path_to_math\n"
# define ERR_EXT  		"Wrong file extension\n"
# define ERR_MLX_INIT 	"MLX init failed\n"
# define ERR_WIN_INIT 	"WIN init failed\n"
# define ERR_MAP_READ 	"Couldn't open map\n"
# define ERR_MALLOC 	"Malloc failed\n"
# define ERR_DD_TEXTURE "Double definition of a texture\n"
# define ERR_DD_COLOR	"Double definition of a color\n"
# define ERR_TEXTURE 	"Texture not found\n"
# define ERR_ADDR		"Texture addr not found\n"
# define ERR_COL_FORMAT	"Invalid color format\n"
# define ERR_CHAR		"Invalid character found\n"
# define ERR_MAP_CHAR	"Invalid map character found\n"
# define ERR_TM_PLAYERS	"Too many players\n"
# define ERR_NO_PLAYERS "No player found\n"
# define ERR_POS_PLAYER	"Invalid position for the player\n"
# define ERR_MAP_BORDER	"Map is not closed\n"

/*-----------------CONFIG----------------*/

# define HEIGHT 		720
# define WIDTH			1280
# define CUBE_SIZE		64
# define SPEED			10.0
# define ROT_SPEED		0.06
# define NB_RAYS 		640
# define HALF_FOV 		30
# define PROJ_DISTANCE	1108

# define PI				3.141592 // 180°
# define PI_2			1.570796 // 90°
# define PI_3_2			4.712389 // 270°
# define _2_PI			6.283184 //	360°
# define DEG_RAD 		0.017453 // 1°
# define ANGLE_INCR 	0.001636 // = 60°/nb_rays(640)

# define LEFT_ARROW 	65361
# define RIGHT_ARROW 	65363
# define FORWARD 		119
# define BACKWARD 		115
# define LEFT 			97
# define RIGHT 			100
# define ESC 			65307

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

enum e_pos
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

typedef struct s_dda
{
	double	angle_sin;
	double	angle_cos;
	double	delta_x;
	double	delta_y;
	double	x;
	double	y;
}	t_dda;

typedef struct s_mlx_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx_data;

typedef struct s_text
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
	int			is_init;
}	t_text;

typedef struct s_frame
{
	t_point		point;
	float		distance;
	double		angle;
	float		height;
	int			axis;
	enum e_pos	wall_face;
}	t_frame;

typedef struct s_player
{
	t_point	map_pos;
	double	ori;
	double	speed;
}	t_player;

typedef struct s_cub3d
{
	void		*mlx;
	void		*mlx_win;
	t_mlx_data	mlx_img;
	t_text		*no_texture;
	t_text		*so_texture;
	t_text		*we_texture;
	t_text		*ea_texture;
	int			floor_color;
	int			ceiling_color;
	int			map_width;
	int			map_height;
	char		**map;
	t_frame		*frame;
	t_player	player;

	int			shade;
	int			shade_dir;
}	t_cub3d;



/****bonus***/
#define MOUSE_SENSITIVITY 0.005
int animation_loop(t_cub3d *map);
void draw_minimap(t_cub3d *map);
void	animation_shading(t_cub3d	*map);
int	mouse_move(int x, int y, t_cub3d *map);

/*************GAME**************/

void			game(t_cub3d *map);
void			create_frame(t_cub3d	*map);
void			draw_slice(t_cub3d *map, t_frame frame, int index);
void			dda(t_cub3d *map, double ray_ori, t_frame *frame);

/************PARSING************/

int				parsing(char *map_file, t_cub3d *map);
int				add_color(char *buff, t_cub3d *map);
int				add_text(char *buff, t_cub3d *map);
int				is_text_valid(t_cub3d *map);
int				check_one_player(char **map);
int				is_map_closed(char **map);
void			get_player_pos(t_cub3d *map);

/************UTILS************/

int				print_error(char *str, int exit_status);
int				check_extension(char *str);
int				is_map_char(char c);
int				is_map_desc(char *buff);
int				is_player_char(char c);
int				map_init(t_cub3d *map);
int				init_map_array(t_cub3d *map, int height, int width);
int				text_init(t_cub3d *map);
unsigned int	ft_strlen_wnl(const char *str);
char			*ft_strdup_wnls(const char *str);
int				array_len(char **array);
int				free_array(char ***array, int err);
int				create_mlx_color(int t, int r, int g, int b);
int				free_texture(t_cub3d *map);
void			free_partial_array(char ***array, int last_alloc);
int				free_all(t_cub3d *map);
int				load_texture(t_text *texture, t_cub3d *map, char *path);
double			correct_angle(double angle);
void			move_forward(t_cub3d *map);
void			move_backward(t_cub3d *map);
void			move_right(t_cub3d *map);
void			move_left(t_cub3d *map);
int				is_blocking_down(t_cub3d *map, int new_x, int new_y);
int				is_blocking_up(t_cub3d *map, int new_x, int new_y);
int				is_blocking_right(t_cub3d *map, int new_x, int new_y);
int				is_blocking_left(t_cub3d *map, int new_x, int new_y);
int				coords_valid(t_cub3d *map, int x, int y);
int				is_wall(t_cub3d *map, int x, int y);
double			get_wall_y(t_dda utils, int up);
void			fill_ver(t_frame *frame, t_cub3d *map, t_dda data, int right);
void			fill_hor(t_frame *frame, t_dda data, int up);
int				get_texture_color(t_text *text, int x, int y);

#endif
