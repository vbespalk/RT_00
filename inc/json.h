
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
}				t_classes;

typedef enum	e_states {
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
}				t_states;

typedef enum	e_modes {
    MODE_ARRAY,
    MODE_DONE,
    MODE_KEY,
    MODE_OBJECT
}				t_modes;

t_checker		ft_checkernew(int depth);
int				ft_check_char(t_checker checker, int c);
int				ft_check_done(t_checker parser);

#endif
