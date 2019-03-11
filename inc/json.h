
#ifndef JSON_H

# define JSON_H

# include "JSON_checker.h"
# include "libftprintf.h"
# include "libpnt.h"

# define OBJ_DEPTH		5

typedef enum			e_datatype
{
	DT_POINT,
	DT_CAMERA,
	DT_OBJECT_ARR,
	DT_LIGHT_ARR,
	DT_STRING,
	DT_COLOR,
	DT_FLOAT,
	DT_COEF,
	DT_BOOL
}						t_datatype;

typedef struct s_scene	t_scene;

/*
**	parse.c
*/

t_scene					*ft_parse_json(char *filename);

/*
**	syntax.c
*/

void					ft_check_syntax(char *content);

/*
**	attribute.c
*/

void					ft_get_attr
							(char **content, char *attr,
							void *dst, t_datatype datatype);

/*
**	attribute_utils.c
*/

void					ft_parse_str
							(char **content, char **data,
							void *dst, t_datatype datatype);
void					ft_parse_json_object
							(char **content, char **data,
							void *dst, t_datatype datatype);
void					ft_parse_json_array
							(char **content, char **data,
							void *dst, t_datatype datatype);
void					ft_parse_num
							(char **content, char **data,
							void *dst, t_datatype datatype);
void					ft_parse_bool
							(char **content, char **data,
							void *dst, t_datatype datatype);

/*
**	warning.c
*/

void					ft_parse_warning_datatype
							(char *content, char *attr, t_datatype datatype);

#endif
