#ifndef CUB3D
#define CUB3D

#include <stdio.h>
# include <mlx.h>
# include <stdlib.h>
#include <math.h>
#include <fcntl.h>
# include "./libft/libft.h"
# include "./gnl/get_next_line.h"
// #include "wall.ppm"

#define RIGHT 2
#define LEFT 0
#define UP 13
#define DOWN 1
#define TRIGHT 124
#define TLEFT 123

typedef struct s_rays
{
	float width;
	int num;
    float vert_wall_hitx;
    float vert_wall_hity;
    float horz_wall_hitx;
    float horz_wall_hity;
    float hdistance;
    float vdistance;
    int up;
    int down;
    int right;
    int left;
    float first_intersectionX;
    float first_intersectionY;
}t_rays;

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
	char *no;
	char *so;
	char *we;
	char *ea;

	int f_rgb[3];
	int c_rgb[3];
    int f;
    int c;
	int player_l_d;

}	t_props;

typedef struct s_line
{
	char *line;
	int len;
} t_line;

struct map
{
	char *line;
	int len;
};

typedef struct s_list_cub
{
	char *line;
	struct s_list_cub *next;
} t_list_map;

typedef struct s_map
{
	char	**array;
	int		rows;
	int		cols;
    void    *wall;
}	t_map;

typedef struct s_ind
{
    int i;
    int index;
} t_index;


typedef struct s_player
{
	float		x;
	float		y;
    int turnDirection;
    int walkDirection;
    int twalkDirection;
    float rotationAngle;
    float moveSpeed;
    float rotationSpeed;
    float fov_angle;
    float move_angle;
}	t_player;


typedef struct s_data
{
    void *mlx;
    void *win;
    float x;
    float y;
    int window_hight;
    int window_width;
    int texture_size;
    int square_size;
    int ud;
    int rl;
    void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
    int     *img_addr[4];
    t_map map;
    t_player player;
    t_rays	rays;
    t_props props;

}t_data;

t_data data;

void    init(char **av);
void	read_map(char *file);
void    draw2D();
void draw3D(float wall_hight , int i, int x_offset, int way);
void    game_start();
void    update();
int     wall_check(float x, float y);
void    cast_rays(int d);
void	my_mini_mlx_pixel_put(int x, int y, int color);
void	my_main_mlx_pixel_put(int x, int y, int color);
int    horizon_check(float ray_angle);
int    vertic_check(float ray_angle);
int hcast(float nextX, float nextY, float hstepx, float hstepy);
int vcast(float nextX, float nextY, float vstepx, float vstepy);
float angle_corrector(float angle);
int sum_of_rgb(int r, int g, int b);
void strip(float x1, float y1, float y2,int x_offset, int w);
void read_textures();

void dda(float x2, float y2);
void main_dda(float x, float y, float x2, float y2, int color);
void	end_game(char *error_message);


/* ////////////////// */
/* ///PARSING UTILS// */


void    pars_props(t_list_map *list);
void	delete_props(t_list_map **list);
void	print_props(t_props props);
void	delete_props(t_list_map **list);
void    init_map(char **av);
void	check_extention(char *file, char *extention);
// void	remove_empty_lines(t_list_map **list);

/*parsing suport*/

void	free_2d_arr(char **arr);
void	remove_empty_lines(t_list_map **list);
int		all_spaces(char *line);
int		ft_strcmp(const char *s1, const char *s2);
void    print_arr(char **lines);
/* ////////////////// */
/* ////////////////// */

/* ////////////////// */
/* ////LIST UTILS//// */



void	add_last(t_list_map **list, char *str);
t_list_map	*creat_list_map(char *file);
t_list_map *delete_node(t_list_map **list, t_list_map *to_delete);
void	print_list_map(t_list_map **tmp);

/* ////////////////// */
/* ////////////////// */
#endif // CUB3d

