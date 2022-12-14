/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 01:41:03 by ael-yamo          #+#    #+#             */
/*   Updated: 2022/10/28 04:15:39 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <mlx.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include "./libft/libft.h"
# include "./gnl/get_next_line.h"

# define RIGHT 2
# define LEFT 0
# define UP 13
# define DOWN 1
# define TRIGHT 124
# define TLEFT 123

typedef struct s_rays
{
	float	width;
	int		num;
	float	vert_wall_hitx;
	float	vert_wall_hity;
	float	horz_wall_hitx;
	float	horz_wall_hity;
	float	hdistance;
	float	vdistance;
	int		up;
	int		down;
	int		right;
	int		left;
	float	first_intersectionx;
	float	first_intersectiony;
	int		x_offset;
}	t_rays;

enum
{
	NO,
	SO,
	WE,
	EA,
	F,
	C
};

typedef struct s_properties
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;

	int		f_rgb[3];
	int		c_rgb[3];
	int		f;
	int		c;
	int		player_l_d;

}	t_props;

typedef struct s_line
{
	char	*line;
	int		len;
}	t_line;

typedef struct s_list_cub
{
	char				*line;
	struct s_list_cub	*next;
}	t_list_map;

typedef struct s_map
{
	char	**array;
	int		rows;
	int		cols;
	void	*wall;
}	t_map;

typedef struct s_ind
{
	int	i;
	int	index;
}	t_index;

typedef struct s_player
{
	float	x;
	float	y;
	int		turn_direction;
	int		walk_direction;
	int		twalk_direction;
	float	r_angle;
	float	move_speed;
	float	r_speed;
	float	fov_angle;
	float	mv_angl;
}	t_player;

typedef struct g_data
{
	void		*mlx;
	void		*win;
	float		x;
	float		y;
	int			window_hight;
	int			window_width;
	int			texture_size;
	int			square_size;
	int			ud;
	int			rl;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			length;
	int			endian;
	int			*img_addr[4];
	t_index		index;
	t_map		map;
	t_player	player;
	t_rays		rays;
	t_props		props;

}t_data;

t_data	g_data;

void		init(char **av);
void		read_map(char *file);
void		draw2d(void);
void		draw3d(float wall_hight, int i, int way);
void		game_start(void);
void		update(void);
int			wall_check(float x, float y);
void		cast_rays(int d);
void		my_mini_mlx_pixel_put(int x, int y, int color);
void		my_main_mlx_pixel_put(int x, int y, int color);
int			horizon_check(float ray_angle);
int			vertic_check(float ray_angle);
int			hcast(float nextX, float nextY, float hstepx, float hstepy);
int			vcast(float nextX, float nextY, float vstepx, float vstepy);
float		angle_corrector(float angle);
int			sum_of_rgb(int r, int g, int b);
void		strip(float x1, float y1, float y2, int w);
void		read_textures(void);
void		check_ray(float ray_angle, int i);

void		dda(float x2, float y2);
void		main_dda(float x, float y, float x2, float y2);
void		end_game(char *error_message);
float		distance(float x, float y);
float		angle_corrector(float angle);
float		implement(float hit_distance, float ray_angle);

/* ////////////////// */
/* ///PARSING UTILS// */

void		pars_props(t_list_map *list);
void		delete_props(t_list_map **list);
void		print_props(t_props props);
void		delete_props(t_list_map **list);
void		init_map(char **av);
void		check_extention(char *file, char *extention);
int			count_list_elms(t_list_map *list);
char		*ft_strdup_n(const char *s1);
t_line		*list_to_arr(t_list_map *list);
void		check_outside(int start, int end, t_line *lines, int index);
int			is_player(char c);
int			check_space(t_line *lines, int index, int i);
void		check_line(t_line *lines, int index);
int			all_spaces(char *line);
void		check_first_line(t_line *lines);
void		check_last_line(t_line *lines, int i);
void		map_is_closed(t_line *lines);
int			check_player(char c);
// void	remove_empty_lines(t_list_map **list);

/*parsing suport*/

void		free_2d_arr(char **arr);
void		remove_empty_lines(t_list_map **list);
int			all_spaces(char *line);
int			ft_strcmp(const char *s1, const char *s2);
void		print_arr(char **lines);
void		check_map_elm(t_line *lines, t_props *props);
void		check_extention(char *file, char *extention);
char		*fill_wall(int (*arr)[6], int n, char *str);
void		ft_striteri2(char **s, void (*f)(char));
void		check_digit(char c);
char		**get_clr_str(char **str);
void		fill_color(int (*arr)[6], int n, int (*colors)[3], char **str);
void		pars_props_utils(char **prop, int (*arr)[6]);
void		pars_props_utils2(int (*arr)[6], int count);
/* ////////////////// */
/* ////////////////// */

/* ////////////////// */
/* ////LIST UTILS//// */

void		add_last(t_list_map **list, char *str);
t_list_map	*creat_list_map(char *file);
t_list_map	*delete_node(t_list_map **list, t_list_map *to_delete);
void		print_list_map(t_list_map **tmp);

/* ////////////////// */
/* ////////////////// */
#endif // CUB3d
