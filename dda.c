/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekundur <mekundur@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:04:38 by mekundur          #+#    #+#             */
/*   Updated: 2024/09/04 20:38:19 by mekundur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	calculate_s(int dx, int dy)
{
	int	s;

	if (dx >= dy || (-1 * dx) >= dy)
	{
		if (dx < 0)
			s = dx * -1;
		else
			s = dx;
	}
	else
	{
		if (dy < 0)
			s = dy * -1;
		else
			s = dy;
	}
	return (s);
}

void	ft_dda_hor(t_type *map, mlx_image_t *img, int i, int j)
{
	float	dx;
	float	dy;
	float	x_inc;
	float	y_inc;
	float	s;

	if ((j + 1) < map->c)
	{
		dx = map->x[i * map->c + j + 1] - map->x[i * map->c + j];
		dy = map->y[i * map->c + j + 1] - map->y[i * map->c + j];
	}
	s = calculate_s(dx, dy);
	y_inc = dy / s;
	x_inc = dx / s;
	while (s >= 0 && j < map->c && i < map->r
		&& map->x[i * map->c + j] < WIDTH
		&& map->y[i * map->c + j] < HEIGHT)
	{
		ft_put_pixel(img, map->x[i * map->c + j], \
				map->y[i * map->c + j], map->color[i * map->c + j]);
		map->x[i * map->c + j] += x_inc;
		map->y[i * map->c + j] += y_inc;
		s--;
	}
}

void	ft_dda_ver(t_type *map, mlx_image_t *img, int i, int j)
{
	float	dx;
	float	dy;
	float	x_inc;
	float	y_inc;
	float	s;

	if ((j + 1) < map->r)
	{
		dx = map->x[(j + 1) * map->c + i] - map->x[j * map->c + i];
		dy = map->y[(j + 1) * map->c + i] - map->y[j * map->c + i];
	}
	s = calculate_s(dx, dy);
	y_inc = dy / s;
	x_inc = dx / s;
	while (s >= 0 && j < map->r && i < map->c
		&& map->x[j * map->c + i] < WIDTH
		&& map->y[j * map->c + i] < HEIGHT)
	{
		ft_put_pixel(img, map->x[j * map->c + i], \
				map->y[j * map->c + i], map->color[j * map->c + i]);
		map->x[j * map->c + i] += x_inc;
		map->y[j * map->c + i] += y_inc;
		s--;
	}
}

void	ft_draw_horizontal(t_type *map, mlx_image_t *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->r)
	{
		j = 0;
		while (j < map->c - 1)
		{
			if (map->x[i * map->c + j] >= 0
				&& map->y[i * map->c + j] >= 0
				&& map->x[i * map->c + j] < WIDTH
				&& map->y[i * map->c + j] < HEIGHT)
				ft_dda_hor(map, img, i, j);
			j++;
		}
		i++;
	}
}

void	ft_draw_vertical(t_type *map, mlx_image_t *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->c)
	{
		j = 0;
		while (j < map->r - 1)
		{
			if (map->x[j * map->c + i] >= 0
				&& map->y[j * map->c + i] >= 0
				&& map->x[j * map->c + i] < WIDTH
				&& map->y[j * map->c + i] < HEIGHT)
				ft_dda_ver(map, img, i, j);
			j++;
		}
		i++;
	}
}
