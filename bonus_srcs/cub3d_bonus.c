/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:31:36 by jadithya          #+#    #+#             */
/*   Updated: 2024/02/05 15:01:41 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

// void	print_map(t_cub3d *cub3d)
// {
// 	int	c;

// 	c = 0;
// 	while (cub3d->map.points[c])
// 	{
// 		if (c > 9)
// 			printf("mapline = %d |%s|\n", c, cub3d->map.points[c]);
// 		else
// 			printf("mapline = %d  |%s|\n", c, cub3d->map.points[c]);
// 		c++;
// 	}
// }

// void	struck_check(t_cub3d *cub3d)
// {
// 	printf("NO texture = %s\n", cub3d->map.t_n);
// 	printf("SO texture = %s\n", cub3d->map.t_s);
// 	printf("EA texture = %s\n", cub3d->map.t_e);
// 	printf("WE texture = %s\n", cub3d->map.t_w);
// 	printf("F = %d\n", cub3d->map.f);
// 	printf("C = %d\n", cub3d->map.c);
// 	printf("player facing = %f\n", cub3d->player.p_angle);
// 	printf("player location = %d, %d\n", cub3d->map.p_row, cub3d->map.p_colom);
// }

void	print_filemap(t_cub3d *cube)
{
	int	i;

	i = 0;
	while (cube->map.file_map[i])
	{
		printf("%d: %s\n", i, cube->map.file_map[i]);
		i++;
	}
}

unsigned int	**t_ext(t_cub3d *cube, char *map)
{

	int	width;
	int	height;
	int	pos;
	cube->img.img = mlx_new_image(cube->mlx, cube->width, cube->height); // new image
	cube->img.img = mlx_xpm_file_to_image(cube->mlx, map, &width, &height); // mlx to image
	char	*name = mlx_get_data_addr(cube->img.img, &cube->img.bpp,
			&cube->img.line_length, &cube->img.endian); // getting the address of the image
	unsigned int	**num;
	int	x;
	int	y = 64;
	num = ft_calloc(65, sizeof(unsigned int *));
	while (y > -1)
	{
		x = 64;
		num[y] = ft_calloc(65, sizeof(unsigned int));
		while (x > -1)
		{
			pos = (y * cube->img.line_length + x * (cube->img.bpp / 8));
			num[y][x] = *(unsigned int *)&name[pos];
			x--;
		}
		y--;
	}
	mlx_destroy_image(cube->mlx, cube->img.img);
	return(num);
}

void	get_text(t_cub3d *cube)
{
	cube->map.i_n = t_ext(cube, cube->map.t_n);
	cube->map.i_s = t_ext(cube, cube->map.t_s);
	cube->map.i_e = t_ext(cube, cube->map.t_e);
	cube->map.i_w = t_ext(cube, cube->map.t_w);
	cube->map.door = t_ext(cube, "textures/doors.xpm");
	
	cube->map.torch0 = t_ext(cube, "Torch64x64_01.xpm");
	cube->map.torch1 = t_ext(cube, "Torch64x64_02.xpm");
	cube->map.torch2 = t_ext(cube, "Torch64x64_03.xpm");
	cube->map.torch3 = t_ext(cube, "Torch64x64_04.xpm");
	cube->map.torch4 = t_ext(cube, "Torch64x64_05.xpm");
	cube->map.torch5 = t_ext(cube, "Torch64x64_06.xpm");
}



void	create_map(t_cub3d *cube)
{
	cube->width = 800;
	cube->height = 800;
	cube->mlx = mlx_init();
	cube->mlx_window = mlx_new_window(cube->mlx, cube->width, cube->height, "");
	get_text(cube);
	draw_map(cube);
}

int	mouse(int x, int y, t_cub3d *cube)
{
	(void) cube;
	(void) y;
	if (x < 400)
		cube->player.p_angle += 1;
	else if (x >= 400)
		cube->player.p_angle -= 1;
	if (cube->player.p_angle <= 0)
		cube->player.p_angle += 360;
	else if (cube->player.p_angle >= 360)
		cube->player.p_angle -= 360;
	return (0);
}

int	main(int argc, char *argv[])
{
	t_cub3d	cube;

	if (argc != 2)
	{
		ft_putstr_fd("WRONG AMOUNT OF ARGUMENTS", 2);
		exit(1);
	}
	openmap(&cube, argv);
	set_booleans(&cube);
	create_map(&cube);
	print_filemap(&cube);
	mlx_hook(cube.mlx_window, 17, 0, close_x, &cube);
	mlx_hook(cube.mlx_window, 2, (1L << 0), keydown, &cube);
	mlx_hook(cube.mlx_window, 3, (1L << 1), keyup, &cube);
	mlx_hook(cube.mlx_window, 6,(1L << 6), mouse, &cube);
	mlx_loop_hook(cube.mlx, move, &cube);
	mlx_loop(cube.mlx);
}
