
/*
**	https://github.com/douglascrockford/JSON-c
*/

#ifndef JSON_H

# define JSON_H

# define TRUE	1
# define FALSE	0
# define GOOD	0xBABAB00E
# define _		-1

# include <stdlib.h>

typedef struct	s_checker
{
    int			valid;
    int			state;
    int			depth;
    int			top;
    int			*stack;
}				*t_checker;

typedef enum	e_classes
{
    C_SPACE,
    C_WHITE,
    C_LCURB,
    C_RCURB,
    C_LSQRB,
    C_RSQRB,
    C_COLON,
    C_COMMA,
    C_QUOTE,
    C_BACKS,
    C_SLASH,
    C_PLUS,
    C_MINUS,
    C_POINT,
    C_ZERO,
    C_DIGIT,
    C_LOW_A,
    C_LOW_B,
    C_LOW_C,
    C_LOW_D,
    C_LOW_E,
    C_LOW_F,
    C_LOW_L,
    C_LOW_N,
    C_LOW_R,
    C_LOW_S,
    C_LOW_T,
    C_LOW_U,
    C_ABCDF,
    C_E,
    C_ETC,
    NR_CLASSES
}				t_classes;



t_checker		ft_checkernew(int depth);
int				ft_check_char(t_checker parser, int c);
int				ft_check_done(t_checker parser);

#endif
