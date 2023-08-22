#include "cub3d.h"

static char	**new_data_dict(void)
{
	char	**dict;

	dict = (char **)malloc(sizeof(char *) * 7);
	dict[0] = "NO";
	dict[1] = "SO";
	dict[2] = "WE";
	dict[3] = "EA";
	dict[4] = "F";
	dict[5] = "C";
	dict[6] = NULL;
	return (dict);
}

static int	set_data(t_cub3d *cub3d, char *data, char **dict)
{
	int	check_dict;
	int	i;

	check_dict = -1;
	i = 0;
	if (!*data)
		return (0);
	while (dict[i])
	{
		if (!ft_strncmp(data, dict[i], ft_strlen(dict[i])))
		{
			if (i < 4)
				cub3d->textures[i] = set_texture(cub3d, data);
			else
			{
				cub3d->colors[i - 4] = set_color(data);
				if (cub3d->colors[i - 4] < 0)
					return (-1);
			}
			check_dict = i;
			break ;
		}
		i++;
	}
	return (check_dict);
}

int	set_visual_data(t_cub3d *cub3d, int fd)
{
	int		i;
	char	*line;
	char	**dict;
	int		check;
	int		result;

	dict = new_data_dict();
	i = 0;
	result = 0;
	line = get_next_line_no_nl(fd);
	while (line && result != 15)
	{
		printf("LÍNEA: %s$\n", line);
		check = set_data(cub3d, line, dict);
		free(line);
		if (check == -1)
			return (0);
		result += check;
		line = get_next_line_no_nl(fd);
		i++;
	}
	printf("Result: %d\n", result);
	if (result != 15)
		return (0); // si resultado no es igual a 15, está mal, no encontró los 6 correspondientes de manera única
	return (1);
}

/*
int	main(void)
{
	char		**matrix;
	int			fd;
	t_cub3d	*cub;

	//set cub3d y texturas/colores

	fd = open("map.ber", O_RDONLY);
	cub = set_cub3d();
	if (set_visual_data(cub, fd) == 1)
		printf("Datos están bien\n");
	else
	{
		printf("Datos están mal\n");
		return (1);
	}
	free_cub3d(cub);
	cub = NULL;
	printf("Libera bien\n");

	//parte del mapa

	matrix = new_map(fd);
	print_matrix(matrix);
	char **normalized = normalize_map(matrix);
	printf("Hace normalized\n");
	print_matrix(normalized);
	free_matrix((void**)matrix);
	free_matrix((void**)normalized);
	printf("Hace bien normalized\n");
	//atexit(&leaks);
	return (0);
}*/
