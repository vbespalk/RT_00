
/*
**	https://github.com/douglascrockford/JSON-c
*/

#include "json.h"

static int		ascii_class[128] = {
/*
**	This array maps the 128 ASCII characters into character classes.
**	The remaining Unicode characters should be mapped to ETC.
**	Non-whitespace control characters are errors.
*/
    _,     _,     _,     _,     _,     _,     _,     _,
    _,     WHITE, WHITE, _,     _,     WHITE, _,     _,
    _,     _,     _,     _,     _,     _,     _,     _,
    _,     _,     _,     _,     _,     _,     _,     _,

    SPACE, ETC,   QUOTE, ETC,   ETC,   ETC,   ETC,   ETC,
    ETC,   ETC,   ETC,   PLUS,  COMMA, MINUS, POINT, SLASH,
    ZERO,  DIGIT, DIGIT, DIGIT, DIGIT, DIGIT, DIGIT, DIGIT,
    DIGIT, DIGIT, COLON, ETC,   ETC,   ETC,   ETC,   ETC,

    ETC,   ABCDF, ABCDF, ABCDF, ABCDF, E,     ABCDF, ETC,
    ETC,   ETC,   ETC,   ETC,   ETC,   ETC,   ETC,   ETC,
    ETC,   ETC,   ETC,   ETC,   ETC,   ETC,   ETC,   ETC,
    ETC,   ETC,   ETC,   LSQRB, BACKS, RSQRB, ETC,   ETC,

    ETC,   LOW_A, LOW_B, LOW_C, LOW_D, LOW_E, LOW_F, ETC,
    ETC,   ETC,   ETC,   ETC,   LOW_L, ETC,   LOW_N, ETC,
    ETC,   ETC,   LOW_R, LOW_S, LOW_T, LOW_U, ETC,   ETC,
    ETC,   ETC,   ETC,   LCURB, ETC,   RCURB, ETC,   ETC
};


static int		state_transition_table[NR_STATES][NR_CLASSES] = {
	{GO,GO,-6,_,-5,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
	{OK,OK,_,-8,_,-7,_,-3,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
	{OB,OB,_,-9,_,_,_,_,S,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
	{KE,KE,_,_,_,_,_,_,S,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
	{CO,CO,_,_,_,_,-2,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
	{VA,VA,-6,_,-5,_,_,_,S,_,_,_,MI,_,ZE,IN,_,_,_,_,_,F1,_,N1,_,_,T1,_,_,_,_},
	{AR,AR,-6,_,-5,-7,_,_,S,_,_,_,MI,_,ZE,IN,_,_,_,_,_,F1,_,N1,_,_,T1,_,_,_,_},
	{S,_,S,S,S,S,S,S,-4,ES,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S},
	{_,_,_,_,_,_,_,_,S,S,S,_,_,_,_,_,_,S,_,_,_,S,_,S,S,_,S,U1,_,_,_},
	{_,_,_,_,_,_,_,_,_,_,_,_,_,_,U2,U2,U2,U2,U2,U2,U2,U2,_,_,_,_,_,_,U2,U2,_},
	{_,_,_,_,_,_,_,_,_,_,_,_,_,_,U3,U3,U3,U3,U3,U3,U3,U3,_,_,_,_,_,_,U3,U3,_},
	{_,_,_,_,_,_,_,_,_,_,_,_,_,_,U4,U4,U4,U4,U4,U4,U4,U4,_,_,_,_,_,_,U4,U4,_},
	{_,_,_,_,_,_,_,_,_,_,_,_,_,_,S,S,S,S,S,S,S,S,_,_,_,_,_,_,S,S,_},
	{_,_,_,_,_,_,_,_,_,_,_,_,_,_,ZE,IN,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
	{OK,OK,_,-8,_,-7,_,-3,_,_,_,_,_,FR,_,_,_,_,_,_,E1,_,_,_,_,_,_,_,_,E1,_},
	{OK,OK,_,-8,_,-7,_,-3,_,_,_,_,_,FR,IN,IN,_,_,_,_,E1,_,_,_,_,_,_,_,_,E1,_},
	{_,_,_,_,_,_,_,_,_,_,_,_,_,_,FS,FS,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
	{OK,OK,_,-8,_,-7,_,-3,_,_,_,_,_,_,FS,FS,_,_,_,_,E1,_,_,_,_,_,_,_,_,E1,_},
	{_,_,_,_,_,_,_,_,_,_,_,E2,E2,_,E3,E3,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
	{_,_,_,_,_,_,_,_,_,_,_,_,_,_,E3,E3,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
	{OK,OK,_,-8,_,-7,_,-3,_,_,_,_,_,_,E3,E3,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
	{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,T2,_,_,_,_,_,_},
	{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,T3,_,_,_},
	{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,OK,_,_,_,_,_,_,_,_,_,_},
	{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,F2,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
	{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,F3,_,_,_,_,_,_,_,_},
	{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,F4,_,_,_,_,_},
	{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,OK,_,_,_,_,_,_,_,_,_,_},
	{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,N2,_,_,_},
	{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,N3,_,_,_,_,_,_,_,_},
	{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,OK,_,_,_,_,_,_,_,_}
};

static void		destroy(t_checker jc)
{
    jc->valid = 0;
    free((void*)jc->stack);
    free((void*)jc);
}

static int		reject(t_checker jc)
{
    destroy(jc);
    return FALSE;
}

static int		push(t_checker jc, int mode)
{
    jc->top += 1;
    if (jc->top >= jc->depth)
        return FALSE;
    jc->stack[jc->top] = mode;
    return TRUE;
}

static int		pop(t_checker jc, int mode)
{
    if (jc->top < 0 || jc->stack[jc->top] != mode)
        return FALSE;
    jc->top -= 1;
    return TRUE;
}

t_checker		ft_checkernew(int depth)
{
    t_checker jc = (t_checker)malloc(sizeof(struct s_checker));
    jc->valid = GOOD;
    jc->state = GO;
    jc->depth = depth;
    jc->top = -1;
    jc->stack = (int *)calloc(depth, sizeof(int));
    push(jc, MODE_DONE);
    return jc;
}

int				ft_check_char(t_checker parser, int c)
{
    int		next_class;
    int		next_state;

    if (parser->valid != GOOD) {
        return FALSE;
    }
    if (c < 0) {
        return reject(parser);
    }
    if (c >= 128) {
        next_class = ETC;
    } else {
        next_class = ascii_class[c];
        if (next_class <= _) {
            return reject(parser);
        }
    }
    next_state = state_transition_table[parser->state][next_class];
    if (next_state >= 0) {
        parser->state = next_state;
    } else {
        switch (next_state) {
        case -9:
            if (!pop(parser, MODE_KEY)) {
                return reject(parser);
            }
            parser->state = OK;
            break;

/* } */ case -8:
            if (!pop(parser, MODE_OBJECT)) {
                return reject(parser);
            }
            parser->state = OK;
            break;

/* ] */ case -7:
            if (!pop(parser, MODE_ARRAY)) {
                return reject(parser);
            }
            parser->state = OK;
            break;

/* { */ case -6:
            if (!push(parser, MODE_KEY)) {
                return reject(parser);
            }
            parser->state = OB;
            break;

/* [ */ case -5:
            if (!push(parser, MODE_ARRAY)) {
                return reject(parser);
            }
            parser->state = AR;
            break;

/* " */ case -4:
            switch (parser->stack[parser->top]) {
            case MODE_KEY:
                parser->state = CO;
                break;
            case MODE_ARRAY:
            case MODE_OBJECT:
                parser->state = OK;
                break;
            default:
                return reject(parser);
            }
            break;

/* , */ case -3:
            switch (parser->stack[parser->top]) {
            case MODE_OBJECT:
                if (!pop(parser, MODE_OBJECT) || !push(parser, MODE_KEY)) {
                    return reject(parser);
                }
                parser->state = KE;
                break;
            case MODE_ARRAY:
                parser->state = VA;
                break;
            default:
                return reject(parser);
            }
            break;

/* : */ case -2:
            if (!pop(parser, MODE_KEY) || !push(parser, MODE_OBJECT)) {
                return reject(parser);
            }
            parser->state = VA;
            break;
        default:
            return reject(parser);
        }
    }
    return TRUE;
}


int				ft_check_done(t_checker parser)
{
    if (parser->valid != GOOD) {
        return FALSE;
    }
    int result = parser->state == OK && pop(parser, MODE_DONE);
    destroy(parser);
    return result;
}



////////////////////////////////////////////////////////////////////////////////



static int	ft_check_bracket(char c, int *counters[3], int last_bracket)
{
	if (c == '(')
	{
		++(*counters[0]);
		return ('(');
	}
	else if (c == '[')
	{
		++(*counters[1]);
		return ('[');
	}
	else if (c == '{')
	{
		++(*counters[2]);
		return ('{');
	}
	else if (c == ')')
}

void		ft_validate(char *content)
{
	char	*c;

	int		line;
	int		symbol;

	int		brackets[3];
	char	last_bracket;



	c = content;

	line = 0;
	symbol = 0;

	last_bracket = 0;

	while (c)
	{
		while (c && ft_isspace(*c))
			++c;
		if (!c)
			return ;

		++c;
	}
}
