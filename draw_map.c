/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekundur <mekundur@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:32:37 by mekundur          #+#    #+#             */
/*   Updated: 2024/09/04 20:31:22 by mekundur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_rotate_project(t_type *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->r)
	{
		j = 0;
		while (j < map->c)
		{
			map->x[i * map->c + j] = (sqrt(2) * (j - i)) / 2;
			map->y[i * map->c + j] = (j + i) / sqrt(6) \
					- sqrt(6) * map->number[(i * map->c + j)] / 3;
			map->z[i * map->c + j] = map->number[i * map->c + j];
			j++;
		}
		i++;
	}
}

void	ft_min_max(t_type *map)
{
	int	i;
	int	j;

	map->x_min = map->x[0];
	map->x_max = map->x[0];
	map->y_min = map->y[0];
	map->y_max = map->y[0];
	i = 0;
	while (i < map->r)
	{
		j = 0;
		while (j < map->c)
		{
			if (map->x[i * map->c + j] < map->x_min)
				map->x_min = map->x[i * map->c + j];
			if (map->x[i * map->c + j] > map->x_max)
				map->x_max = map->x[i * map->c + j];
			if (map->y[i * map->c + j] < map->y_min)
				map->y_min = map->y[i * map->c + j];
			if (map->y[i * map->c + j] > map->y_max)
				map->y_max = map->y[i * map->c + j];
			j++;
		}
		i++;
	}
}

void	ft_scale(t_type	*map)
{
	int	i;
	int	j;

	map->width = WIDTH - 100;
	map->height = HEIGHT - 100;
	map->length_x = map->x_max - map->x_min;
	map->length_y = map->y_max - map->y_min;
	if ((map->height / map->length_y) <= (map->width / map->length_x))
		map->dscale = map->height / (map->length_y);
	else
		map->dscale = map->width / (map->length_x);
	i = 0;
	while (i < map->r)
	{
		j = 0;
		while (j < map->c)
		{
			map->x[i * map->c + j] *= map->dscale;
			map->y[i * map->c + j] *= map->dscale;
			j++;
		}
		i++;
	}
}

void	ft_translate(t_type *map)
{
	int		i;
	int		j;
	float	delta_x;
	float	delta_y;

	delta_x = (WIDTH - map->x_max - map->x_min) / 2;
	delta_y = (HEIGHT - map->y_max - map->y_min) / 2;
	i = 0;
	while (i < map->r)
	{
		j = 0;
		while (j < map->c)
		{
			map->x[i * map->c + j] += delta_x;
			map->y[i * map->c + j] += delta_y;
			j++;
		}
		i++;
	}
}

void	ft_draw_map(t_type *map, mlx_image_t *img)
{
	map->x = (float *)malloc(map->c * map->r * sizeof(float));
	map->y = (float *)malloc(map->c * map->r * sizeof(float));
	map->z = (float *)malloc(map->c * map->r * sizeof(float));
	if (!map->x || !map->y || !map->z)
		return (ft_free_all(map));
	ft_rotate_project(map);
	ft_min_max(map);
	ft_scale(map);
	ft_min_max(map);
	ft_translate(map);
	ft_draw_horizontal(map, img);
	ft_rotate_project(map);
	ft_min_max(map);
	ft_scale(map);
	ft_min_max(map);
	ft_translate(map);
	ft_draw_vertical(map, img);
}
