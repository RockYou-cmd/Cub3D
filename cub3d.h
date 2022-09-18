#ifndef CUB3D
#define CUB3D

#include <stdio.h>
# include <mlx.h>
# include <stdlib.h>
#include <math.h>
#include <fcntl.h>
# include "./libft/libft.h"
# include "./gnl/get_next_line.h"

#define RIGHT 2
#define LEFT 0
#define UP 13
#define DOWN 1
#define TRIGHT 124
#define TLEFT 123

typedef struct s_rays
{
	float width;
    int vhited;
    int hhited;
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

typedef struct s_map
{
	char	**array;
	int		rows;
	int		cols;
}	t_map;

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
    int square_size;
    t_map map;
    t_player player;
    t_rays	rays;
    void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}t_data;

t_data data;

void    init(char **av);
void	read_map(char *file);
void    draw();
void    game_start();
void    update();
int     wall_check(float x, float y);
void    cast_rays();
void	my_mini_mlx_pixel_put(int x, int y, int color);
void	my_main_mlx_pixel_put(int x, int y, int color);
int    horizon_check(float ray_angle);
int    vertic_check(float ray_angle);
int hcast(float nextX, float nextY);
int vcast(float nextX, float nextY);
float angle_corrector(float angle);
int sum_of_rgb(int t, int r, int g, int b);

void dda(float x2, float y2);
void main_dda(float x, float y, float x2, float y2, int color);
void	end_game(char *error_message);


#endif // CUB3d

