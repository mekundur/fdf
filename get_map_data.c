/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekundur <mekundur@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:32:23 by mekundur          #+#    #+#             */
/*   Updated: 2024/09/04 11:58:09 by mekundur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_coloumn_count(char *argv)
{
	int		fd;
	int		col;
	char	*line;
	char	**tmp;

	col = 0;
	fd = open(argv, O_RDONLY);
	line = get_next_line(fd);
	tmp = ft_split(line, ' ');
	while (tmp[col])
	{
		if (!((tmp[col][0] >= '0' && tmp[col][0] <= '9') || tmp[col][0] == '-'))
			break ;
		col++;
	}
//	close(fd);
	free(line);
	free_ft_split_array(tmp);
	return (col);
}

int	ft_row_count(char *argv)
{
	int		row;
	int		fd;
	char	*tmp;

	row = 0;
	tmp = "1";
	fd = open(argv, O_RDONLY);
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		free(tmp);
		row++;
	}
	close(fd);
	return (row);
}

void	put_data(t_type *map, char **str, int i, int j)
{
	if (str[j])
	{
		map->number[(i * map->c) + j] = ft_atoi(str[j]);
		map->color[(i * map->c) + j] = \
				ft_atoi_hex(ft_strnstr(str[j], "0x", 12));
		if (map->color[(i * map->c) + j] == 0)
			map->color[(i * map->c) + j] = 0xFFFFFFFF;
		else
			map->color[(i * map->c) + j] = \
				(map->color[(i * map->c) + j] << 8) + 0xFF;
	}
	else
	{
		map->number[(i * map->c) + j] = 0;
		map->color[(i * map->c) + j] = 0xFFFFFFFF;
	}
}

void	get_data(char *argv, t_type *map)
{
	int		i;
	int		j;
	int		fd;
	char	**str;
	char	*line;

	fd = open(argv, O_RDONLY);
	i = 0;
	while (i < map->r)
	{
		line = get_next_line(fd);
		str = ft_split(line, ' ');
		j = 0;
		while (j < map->c)
		{
			put_data(map, str, i, j);
			j++;
		}
		free(line);
		free_ft_split_array(str);
		i++;
	}
	close (fd);
}

t_type	*get_map_data(char *argv, t_type *map)
{
	map = (t_type *)malloc(sizeof(t_type));
	if (!map)
		return (0);
	map->r = ft_row_count(argv);
	map->c = ft_coloumn_count(argv);
	map->number = (int *)malloc(map->c * map->r * sizeof(int));
	map->color = (int *)malloc(map->c * map->r * sizeof(int));
	if (!map->color || !map->number)
		return (0);
	get_data(argv, map);
	return (map);
}
