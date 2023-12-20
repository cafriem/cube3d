/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 16:21:03 by cafriem           #+#    #+#             */
/*   Updated: 2023/12/20 18:14:41 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <stdbool.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <signal.h>
# include "../libft/libft.h"
 # include <mlx.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

# define PIE 3.14
# define COS046 0.89438856137
# define SIN046 0.4472908464
// # ifdef OSX
# define ESC 53
# define PLUS 24
# define MINUS 27
# define W 13
# define A 0
# define S 1
# define D 2
# define LEFT 123
# define RIGHT 124
# define DOWN 125
# define UP 126
# define R 15
# define F 3
# define X 7
# define Q 12
# define E 14
# define H 4
# define K 40
# define I 34
# define J 38
# define L 37
# define C 8
// # elif LINUX
//# include "../mlx-linux/mlx.h"
//# define ESC 65307
//# define Q 113
//# define W 119
//# define E 101
//# define R 114
//# define A 97
//# define S 115
//# define D 100
//# define F 102
//# define Z 122
//# define X 120
//# define C 99
//# define V 118
//# define UP 65362
//# define DOWN 65364
//# define LEFT 65361
//# define RIGHT 65363
//# define SHIFT 65307
// # endif

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}		t_data;

typedef struct map {
	char	**points;
	char	**file_map;
	int		width;
	int		height;
	char	*t_n;
	char	*t_s;
	char	*t_e;
	char	*t_w;
	int		p_row;
	int		p_colom;
	int		f;
	int		c;
}		t_map;

typedef struct angles {
	bool	w;
	bool	s;
	bool	a;
	bool	d;
	bool	left;
	bool	right;
}		t_dir;

typedef struct player {
	float	p_angle;
	float	p_dy;
	float	p_dx;
	float	p_y;
	float	p_x;
}		t_player;

typedef struct cub3d {
	int			width;
	int			height;
	void		*mlx;
	void		*mlx_window;
	t_data		img;
	t_map		map;
	t_player	player;
	t_dir		dir;
}		t_cub3d;

typedef struct point {
	int	x;
	int	y;
}		t_point;

//------------DDA.c------------//
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_point(t_cub3d *cube3d);
//------------key_press.c------------//
int		key_press1(int keypress, t_cub3d *cub3d);
void	key_press2(int keypress, t_cub3d *cub3d);
void	key_press3(int keypress, t_cub3d *cub3d);
void	key_press4(int keypress, t_cub3d *cub3d);
void	key_press5(int keypress, t_cub3d *cub3d);
//------------legends.c------------//
void	legends1(t_cub3d *cub3d);
void	legends2(t_cub3d *cub3d);
//------------error.c------------//
void	error(t_cub3d *cub3d, int flag);
//functions:
void	create_map(t_cub3d *cube);
int		close_x(t_cub3d *cube);
int		close_esc(int keycode, t_cub3d *cube);
void	pixel_put(t_data *data, int x, int y, int color);

int		keydown(int keycode, t_cub3d *cube);
int		keyup(int keycode, t_cub3d *cube);

void	draw_map(t_cub3d *cube);

void	dda(t_point x1, t_point x2, t_cub3d *cube, int color);

double	deg2rad(double degrees);

#endif