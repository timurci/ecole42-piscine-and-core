/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hece <hece@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:33:37 by hece              #+#    #+#             */
/*   Updated: 2023/05/26 20:37:29 by hece             ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "vector3.h"
# include "vector3_utils.h"
# include "vector3_utils_extended.h"
# include "ray3.h"
# include "color3.h"
# include "point3.h"

# include "objects.h"
# include "object_parameters.h"
# include "object_sphere.h"
# include "object_camera.h"
# include "object_light.h"

# include "get_next_line.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_compulsory
{
	bool	c;
	bool	a;
	bool	l;
}	t_compulsory;

typedef struct s_split_tmp
{
	char	**split_tmp0;
	char	**split_tmp1;
	char	**split_tmp2;
}	t_split_tmp;

typedef struct s_atof_param
{
	int		iter;
	int		dop;
	float	result;
	float	fraction;
	int		fraction_count;
}				t_atof_param;

void		object_init(t_objects *objects);

char		**ft_split(char const *s, char c);
t_objects	*parse(const char *filename, const float aspect_ratio);
size_t		ft_strlen(const char *str);
char		*ft_strdup(const char *str);
double		ft_pow(double base, int exponent);
float		ft_atof(const char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t size);
void		free_split(char **split);
void		free_split_check_func(char **split);
size_t		ft_check_comma(char *split, char c);

// ERROR FUNCTION

void		ft_plane_error_check(char **split, t_objects *objects);
void		ft_light_error_check(char **split, t_objects *objects);
void		ft_ambient_light_error_check(char **split, t_objects *objects);
void		ft_camera_error_check(char **split, t_objects *objects);
void		ft_sphere_error_check(char **split, t_objects *objects);
void		ft_compulsory(t_compulsory *test, char **split);
void		ft_compulsory_check(t_compulsory *test, t_objects *objects);
void		ft_cylinder_check_error(char **split, t_objects *objects);

t_objects	*create_plane(char **split, t_objects *objects);
t_objects	*create_cylinder(char **split, t_objects *objects);
t_objects	*create_light(char **split, t_objects *objects);
t_objects	*create_ambient_light(char **split, t_objects *objects);
t_objects	*create_camera(char **split, t_objects *objects,
				const float aspect_ratio);
t_objects	*create_sphere(char **split, t_objects *objects);
void		ft_free_tmp_split(t_split_tmp *tmp);

#endif
