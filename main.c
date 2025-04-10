/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekundur <mekundur@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:32:37 by mekundur          #+#    #+#             */
/*   Updated: 2024/09/04 20:31:22 by mekundur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_put_pixel(mlx_image_t *img, int x, int y, int color)
{
	uint8_t	*pixel;

	pixel = &img->pixels[(y * img->width + x) * 4];
	*(pixel++) = (uint8_t)(color >> 24);
	*(pixel++) = (uint8_t)(color >> 16);
	*(pixel++) = (uint8_t)(color >> 8);
	*(pixel++) = (uint8_t)(color & 0xFF);
}

void	ft_free_all(t_type *map)
{
	if (map && map->number)
		free(map->number);
	if (map && map->color)
		free(map->color);
	if (map && map->x)
		free(map->x);
	if (map && map->y)
		free(map->y);
	if (map && map->z)
		free(map->z);
	if (map)
		free(map);
}

void	ft_hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

int	input_check(int argc, char *argv)
{
	if (argc == 1)
		return (ft_printf("Please pass a map in .fdf file format\n"), 0);
	if (argc > 2)
		return (ft_printf("Can't handle more then one map :/\n"), 0);
	if ((open(argv, O_RDONLY) == -1))
		return (ft_printf("non-existing file or no right to read!\n"), 0);
	if (argc == 2 && !ft_strnstr(argv, ".fdf", ft_strlen(argv)))
		return (ft_printf("Please pass a map in .fdf file format\n"), 0);
	if (argc == 2 && !get_next_line(open(argv, O_RDONLY)))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_type			*map;
	mlx_t			*mlx;
	mlx_image_t		*img;

	map = NULL;
	mlx = NULL;
	img = NULL;
	if (!input_check(argc, argv[1]))
		return (0);
	mlx = mlx_init(WIDTH, HEIGHT, "fdf", 1);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!mlx || !img)
		return (0);
	if (mlx_image_to_window(mlx, img, 0, 0) == -1)
		return (0);
	map = get_map_data(argv[1], map);
	if (!map || !map->number || !map->color)
		return (ft_free_all(map), 0);
	ft_draw_map(map, img);
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (ft_free_all(map), 0);
}
