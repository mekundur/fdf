/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekundur <mekundur@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:32:21 by mekundur          #+#    #+#             */
/*   Updated: 2024/09/04 20:39:08 by mekundur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <math.h>
# include "libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"

# define WIDTH 2500
# define HEIGHT 1500

typedef struct s_map_data
{
	int		*number;
	int		*color;
	int		c;
	int		r;
	float	dscale;
	int		width;
	int		height;
	float	x_min;
	float	x_max;
	float	y_min;
	float	y_max;
	float	length_x;
	float	*x;
	float	*y;
	float	*z;
	float	length_y;
	float	dx;
	float	dy;
	float	s;
	float	x_inc;
	float	y_inc;

}	t_type;

t_type		*get_map_data(char *argv, t_type *map);
int			ft_column_count(char *argv);
int			ft_row_count(char *argv);
void		ft_free_all(t_type *map);
void		ft_draw_map(t_type *map, mlx_image_t *img);
void		ft_draw_horizontal(t_type *map, mlx_image_t *img);
void		ft_draw_vertical(t_type *map, mlx_image_t *img);
void		ft_dda_hor(t_type *map, mlx_image_t *img, int i, int j);
void		ft_dda_ver(t_type *map, mlx_image_t *img, int i, int j);
void		ft_put_pixel(mlx_image_t *img, int x, int y, int color);

#endif
