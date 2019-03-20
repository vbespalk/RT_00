
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
<<<<<<< HEAD
	DT_SKYBOX
}					t_datatype;

typedef enum 		e_otype
{
	O_PLANE,
	O_SPHERE,
	O_CONE,
	O_COUNT
}					t_otype;

typedef enum		e_classes
{
    SPACE,
    WHITE,
    LCURB,
    RCURB,
    LSQRB,
    RSQRB,
    COLON,
    COMMA,
    QUOTE,
    BACKS,
    SLASH,
    PLUS,
    MINUS,
    POINT,
    ZERO,
    DIGIT,
    LOW_A,
    LOW_B,
    LOW_C,
    LOW_D,
    LOW_E,
    LOW_F,
    LOW_L,
    LOW_N,
    LOW_R,
    LOW_S,
    LOW_T,
    LOW_U,
    ABCDF,
    E,
    ETC,
    NR_CLASSES
}					t_classes;

typedef enum		e_states
{
    GO,
    OK,
    OB,
    KE,
    CO,
    VA,
    AR,
    S,
    ES,
    U1,
    U2,
    U3,
    U4,
    MI,
    ZE,
    IN,
    FR,
    FS,
    E1,
    E2,
    E3,
    T1,
    T2,
    T3,
    F1,
    F2,
    F3,
    F4,
    N1,
    N2,
    N3,
    NR_STATES
}					t_states;

typedef enum		e_modes
{
    MODE_ARRAY,
    MODE_DONE,
    MODE_KEY,
    MODE_OBJECT
}					t_modes;
=======
	DT_BOOL
}						t_datatype;
>>>>>>> refr_debug

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
