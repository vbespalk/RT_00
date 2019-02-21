
#include "rt.h"

t_vector	ft_parse_point(char *content)
{
	float		coords[3];
	t_vector	point;

	ft_get_attr(content, &(coords[0]), "x", DT_FLOAT);
	ft_get_attr(content, &(coords[1]), "y", DT_FLOAT);
	ft_get_attr(content, &(coords[2]), "z", DT_FLOAT);
	point[0] = coords[0];
	point[1] = coords[1];
	point[2] = coords[2];
	return (point);
}

void		ft_parse_str
				(char *content, char **data, void *dst, t_datatype datatype)
{
	++(*data);
	if (datatype == DT_STRING)
		*((char **)dst) = ft_strcut(
			*data, 0, ft_strchr(*data, '\"') - *data);
	else if (datatype == DT_COLOR)
		(*((int *)dst)) = ft_limit(
			0, 0xffffff, (int)ft_atoi_base(*data, 16));
	else
		ft_parse_warning_datatype(content, *data, datatype);
}

void		ft_parse_json_object
				(char *content, char **data, void *dst, t_datatype datatype)
{
	if (datatype == DT_POINT)
		*((t_vector *)dst) = ft_parse_point(*data);
	if (datatype == DT_CAMERA)
		ft_parse_camera(*data, *((t_camera **)dst));
	else
		ft_parse_warning_datatype(content, *data, datatype);
}

void		ft_parse_array
				(char **data, t_list *list,
				void (*ft_parse)(char *, t_list *, Uint32))
{
	int		scope;
	int		i;
	int		is_in_str;
	Uint32	id;

	scope = 0;
	i = 0;
	is_in_str = 0;
	id = 0;
	while (scope != 0 || *data[++i] != ']' || is_in_str)
	{
		if (*data[i] == '\"' && *data[i - 1] != '\\')
			is_in_str = !is_in_str;
		if (is_in_str)
			continue ;
		if (*data[i] == '{')
		{
			if (scope == 0)
				ft_parse(&(*data[i]), list, id++);
			++scope;
		}
		else if (*data[i] == '}')
			--scope;
	}
}

void		ft_parse_json_array
				(char *content, char **data, void *dst, t_datatype datatype)
{
	if (datatype == DT_LIGHT_ARR || datatype == DT_OBJECT_ARR)
		ft_parse_array(
			data,
			*((t_list **)dst),
			(datatype == DT_LIGHT_ARR) ? ft_parse_light : ft_parse_object
		);
	else
		ft_parse_warning_datatype(content, *data, datatype);
}

void		ft_parse_num
				(char *content, char **data, void *dst, t_datatype datatype)
{
	if (datatype == DT_FLOAT)
		*((float *)dst) = (float)ft_atod(*data);
	else if (datatype == DT_KOEF)
		*((float *)dst) = (float)ft_limitf(0.0, 1.0, (float)ft_atod(*data));
	else
		ft_parse_warning_datatype(content, *data, datatype);
}