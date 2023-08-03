/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 12:02:39 by pfuentes          #+#    #+#             */
/*   Updated: 2023/08/02 10:20:10 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	max_array_len_matrix(char **matrix)
{
	int	i;
	int	max;
	int	len;

	i = 0;
	max = 0;
	while (matrix[i])
	{
		len = ft_strlen(matrix[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

static char	*copy_fill_array(int new_len, char *arr, char fill)
{
	char	*new_arr;
	int		old_len;
	int		i;

	new_arr = (char *)malloc(new_len + 1);
	old_len = ft_strlen(arr);
	i = 0;
	while (i < old_len)
	{
		new_arr[i] = arr[i];
		i++;
	}
	while (i < new_len)
	{
		new_arr[i] = fill;
		i++;
	}
	new_arr[i] = '\0';
	return (new_arr);
}

char	**normalize_map(char **map)
{
	char	**normalize;
	int		max;
	int		i;

	normalize = (char **)malloc(sizeof(char *) * (matrix_len(map) + 1));
	i = 0;
	max = max_array_len_matrix(map);
	printf("Línea de longitud maxima: %d\n", max);
	while (map[i])
	{
		normalize[i] = copy_fill_array(max, map[i], ' ');
		i++;
	}
	normalize[i] = NULL;
	return (normalize);
}
