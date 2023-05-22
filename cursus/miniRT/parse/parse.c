#include "parse.h"

double
	ft_pow(double base, int exponent)
{
	double	result;
	int		count;
	int		exponent_positive;
	double	one;
	
	result = 1.0;
	count = 0;
	exponent_positive = exponent;
	one = 1.0;
	if (exponent < 0)
		exponent_positive = -exponent;
	while(count < exponent_positive)
	{
		result *= base;
		count++;
	}
	if (exponent < 0)
		result = one / result;
	return (result);
}

float
	ft_atof(const char *str)
{
	int		iter;
	int		dop;
	float	result;
	float	fraction;
	int		fraction_count;

	iter = 0;
	dop = 1;
	result = 0;
	fraction = 0;
	fraction_count = 1;
	while ((str[iter] >= '\t' && str[iter] <= '\r') || str[iter] == ' ')
		iter++;
	if (str[iter] == '+' || str[iter] == '-')
	{
		if (str[iter] == '-')
			dop *= -1;
		iter++;
	}
	while (str[iter] >= '0' && str[iter] <= '9' && str[iter] != '\0')
	{
		result = ((str[iter] - '0') + (result * 10));
		iter++;
	}
	if (str[iter] == '.')
		iter++;
	while (str[iter] >= '0' && str[iter] <= '9' && str[iter] != '\0')
	{
		fraction = fraction + (str[iter] - '0') / (float) ft_pow(10, fraction_count);
		fraction_count++;
		iter++;
	}
	return (dop * (result + fraction));
}

int
	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	else
		return (c);
}

char
	*ft_strtolower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

int
	ft_strncmp(const char *s1, const char *s2, size_t size)
{
	size_t		i;
	const char	*s1_lower;
	const char	*s2_lower;

	//s1_lower = ft_strtolower(ft_strdup(s1));
	//s2_lower = ft_strtolower(ft_strdup(s2));
	s1_lower = s1;
	s2_lower = s2;
	i = 0;
	while (i < size && (s1_lower[i] != '\0' || s2_lower[i] != '\0'))
	{
		if (s1_lower[i] != s2_lower[i])
		{
			//free(s1_lower);
			//free(s2_lower);
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	//free(s1_lower);
	//free(s2_lower);
	return (0);
}

void
	free_split(char **split)
{
	char	**ptr;

	if (split == NULL)
		return ;
	ptr = split;
	while (*ptr != NULL)
	{
		free(*ptr);
		ptr++;
	}
	free(split);
}

t_objects
	*create_plane(char **split, t_objects *objects)
{
	t_point3	position;
	t_vec3		normal;
	t_color3	color;
	char		**split_tmp0;
	char		**split_tmp1;
	char		**split_tmp2;
	
	split_tmp0 = ft_split(split[0], ',');
	position.x = ft_atof(split_tmp0[0]);
	position.y = ft_atof(split_tmp0[1]);
	position.z = ft_atof(split_tmp0[2]);
	split_tmp1 = ft_split(split[1], ',');
	normal.x = ft_atof(split_tmp1[0]);
	normal.y = ft_atof(split_tmp1[1]);
	normal.z = ft_atof(split_tmp1[2]);
	split_tmp2 = ft_split(split[2], ',');
	color.x = ft_atof(split_tmp2[0]) / 255.999f;
	color.y = ft_atof(split_tmp2[1]) / 255.999f;
	color.z = ft_atof(split_tmp2[2]) / 255.999f;
	objects->plane = add_plane(objects->plane, position, normal, color);
	free_split(split_tmp0);
	free_split(split_tmp1);
	free_split(split_tmp2);
	return (objects);
}

t_objects
	*create_light(char **split, t_objects *objects)
{
	t_point3	position;
	float		intensity;
	t_color3	color;
	char		**split_tmp0;
	char		**split_tmp2;
	
	split_tmp0 = ft_split(split[0], ',');
	position.x = ft_atof(split_tmp0[0]);
	position.y = ft_atof(split_tmp0[1]);
	position.z = ft_atof(split_tmp0[2]);
	intensity = ft_atof(split[1]);
	split_tmp2 = ft_split(split[2], ',');
	color.x = ft_atof(split_tmp2[0]) / 255.999f;
	color.y = ft_atof(split_tmp2[1]) / 255.999f;
	color.z = ft_atof(split_tmp2[2]) / 255.999f;
	objects->point_light = set_point_light(color, intensity, position);
	free_split(split_tmp0);
	free_split(split_tmp2);
	return (objects);
}

t_objects
	*create_ambient_light(char **split, t_objects *objects)
{
	float		intensity;
	t_color3	color;
	char		**split_tmp;
	
	intensity = ft_atof(split[0]);
	split_tmp = ft_split(split[1], ',');
	color.x = ft_atof(split_tmp[0]) / 255.999f;
	color.y = ft_atof(split_tmp[1]) / 255.999f;
	color.z = ft_atof(split_tmp[2]) / 255.999f;
	objects->ambient_light = set_ambient_light(color, intensity);
	free_split(split_tmp);
	return (objects);
}

t_objects
	*create_camera(char **split, t_objects *objects, const float aspect_ratio)
{
	t_vec3	position;
	t_vec3	direction;
	float	fov;
	char	**split_tmp0;
	char	**split_tmp1;
	
	split_tmp0 = ft_split(split[0], ',');
	split_tmp1 = ft_split(split[1], ',');
	fov = ft_atof(split[2]);
	position.x = ft_atof(split_tmp0[0]);
	position.y = ft_atof(split_tmp0[1]);
	position.z = ft_atof(split_tmp0[2]);
	direction.x = ft_atof(split_tmp1[0]);
	direction.y = ft_atof(split_tmp1[1]);
	direction.z = ft_atof(split_tmp1[2]);
	objects->camera = camera_set(aspect_ratio, fov, direction, position);
	free_split(split_tmp0);
	free_split(split_tmp1);
	return (objects);
}

t_objects
	*create_sphere(char **split, t_objects *objects)
{
	t_point3	center;
	float		radius;
	t_color3	color;
	char		**split_tmp0;
	char		**split_tmp2;

	split_tmp0 = ft_split(split[0], ',');
	center.x = ft_atof(split_tmp0[0]);
	center.y = ft_atof(split_tmp0[1]);
	center.z = ft_atof(split_tmp0[2]);
	radius = ft_atof(split[1]);
	split_tmp2 = ft_split(split[2], ',');
	color.x = ft_atof(split_tmp2[0]) / 255.999f;
	color.y = ft_atof(split_tmp2[1]) / 255.999f;
	color.z = ft_atof(split_tmp2[2]) / 255.999f;
	objects->sphere = add_sphere(objects->sphere, center, radius, color);
	free_split(split_tmp0);
	free_split(split_tmp2);
	return (objects);
}

t_objects
	*create_cylinder(char **split, t_objects *objects)
{
	t_point3			position;
	t_cylinder_params	params;
	t_color3			color;
	char				**split_tmp0;
	char				**split_tmp1;
	char				**split_tmp4;
	
	split_tmp0 = ft_split(split[0], ',');
	position.x = ft_atof(split_tmp0[0]);
	position.y = ft_atof(split_tmp0[1]);
	position.z = ft_atof(split_tmp0[2]);
	split_tmp1 = ft_split(split[1], ',');
	params.radius = ft_atof(split[2]) / 2.0f;
	params.height = ft_atof(split[3]);
	params.axis.x = ft_atof(split_tmp1[0]);
	params.axis.y = ft_atof(split_tmp1[1]);
	params.axis.z = ft_atof(split_tmp1[2]);
	split_tmp4 = ft_split(split[4], ',');
	color.x = ft_atof(split_tmp4[0]) / 255.999f;
	color.y = ft_atof(split_tmp4[1]) / 255.999f;
	color.z = ft_atof(split_tmp4[2]) / 255.999f;
	objects->cylinder = add_cylinder(objects->cylinder, position, params, color);
	free_split(split_tmp0);
	free_split(split_tmp1);
	free_split(split_tmp4);
	return (objects);
}

t_objects
	*create_objects(char **split, t_objects *objects, const float aspect_ratio)
{
	if (ft_strncmp(split[0], "C", 1) == 0)
		objects = create_camera(split + 1, objects, aspect_ratio);
	else if (ft_strncmp(split[0], "sp", 2) == 0)
		objects = create_sphere(split + 1, objects);
	else if (ft_strncmp(split[0], "cy", 2) == 0)
		objects = create_cylinder(split + 1, objects);
	else if (ft_strncmp(split[0], "pl", 2) == 0)
		objects = create_plane(split + 1, objects);
	else if (ft_strncmp(split[0], "L", 1) == 0)
		objects = create_light(split + 1, objects);
	else if (ft_strncmp(split[0], "A", 1) == 0)
		objects = create_ambient_light(split + 1, objects);
	return (objects);
}

t_objects
	*parse_objects(int fd, const float aspect_ratio)
{
	t_objects	*objects;
	char		*line;
	char		**split;
	int 		index;

	index = -1;
	objects = (t_objects *)malloc(sizeof(*objects));
	objects->sphere = NULL;
	objects->plane = NULL;
	objects->cylinder = NULL;
	while ((line = get_next_line(fd)) != NULL)
	{
		split = ft_split(line, ' ');
		objects = create_objects(split, objects, aspect_ratio);
		free(line);
		while (++index && split[index] != NULL)
			free(split[index]);
		index = -1;
		free(split);
	}
	free(line);
	return (objects);
}

t_objects
	*parse(const char *filename, const float aspect_ratio)
{
	int			fd;
	t_objects	*objects;

	fd = open(filename, O_RDWR);
	if (fd == -1)
		return (NULL);
	objects = parse_objects(fd, aspect_ratio);
	if (close(fd) == -1)
		return (NULL);
	return (objects);
}
