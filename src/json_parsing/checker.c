
/*
**	https://github.com/douglascrockford/JSON-c
*/

#include "json.h"

static int		ascii_class[128] = {
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
	{GO,GO,-6,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
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

static int		ft_handle_coma_and_quotation(t_checker ch, int next_state)
{
	if (next_state == -4)
	{
		if (ch->stack[ch->top] == MODE_KEY)
			ch->state = CO;
		else if (ch->stack[ch->top] == MODE_ARRAY ||
				ch->stack[ch->top] == MODE_OBJECT)
			ch->state = OK;
		else
			return (FALSE);
	}
	else if (next_state == -3)
	{
		if (ch->stack[ch->top] == MODE_OBJECT)
		{
			if (!ft_pop(ch, MODE_OBJECT) || !ft_push(ch, MODE_KEY))
            	return (FALSE);
			ch->state = KE;
		}
		else if (ch->stack[ch->top] == MODE_ARRAY)
			ch->state = VA;
		else
			return (FALSE);
	}
	return (TRUE);
}

static int		ft_handle_neg_states(t_checker ch, int next_state)
{
	if (next_state == -9)
    	return (ft_handle_next_state(ch, 0, MODE_KEY, OK));
	else if (next_state == -8)
    	return (ft_handle_next_state(ch, 0, MODE_OBJECT, OK));
	else if (next_state == -7)
    	return (ft_handle_next_state(ch, 0, MODE_ARRAY, OK));
	else if (next_state == -6)
    	return (ft_handle_next_state(ch, 1, MODE_KEY, OB));
	else if (next_state == -5)
    	return (ft_handle_next_state(ch, 1, MODE_ARRAY, AR));
	else if (next_state == -4 || next_state == -3)
		return (ft_handle_coma_and_quotation(ch, next_state));
	else if (next_state == -2)
		return (ft_handle_next_state(ch, 0, MODE_KEY, VA) &&
				ft_handle_next_state(ch, 1, MODE_OBJECT, VA));
	else
		return (FALSE);
}

t_checker		ft_checkernew(int depth)
{
    t_checker checker;

    checker = (t_checker)ft_smemalloc(
    	sizeof(struct s_checker), "ft_checkernew for struct");
    checker->valid = GOOD;
    checker->state = GO;
    checker->depth = depth;
    checker->top = -1;
    checker->stack = (int *)ft_smemalloc(
    	depth * sizeof(int), "ft_checkernew for stack");
	ft_push(checker, MODE_DONE);
    return (checker);
}

int				ft_check_char(t_checker checker, int c)
{
    int		next_class;
    int		next_state;

    if (checker->valid != GOOD)
        return (FALSE);
    if (c < 0)
        return (ft_reject(checker));
    if (c >= 128)
        next_class = ETC;
    else
	{
        next_class = ascii_class[c];
        if (next_class <= _)
            return (ft_reject(checker));
	}
    next_state = state_transition_table[checker->state][next_class];
    if (next_state >= 0)
	{
        checker->state = next_state;
        return (TRUE);
	}
    else
    	return ((ft_handle_neg_states(checker, next_state)) ?
    		TRUE : ft_reject(checker));
}

int				ft_check_done(t_checker parser)
{
	int		res;

    if (parser->valid != GOOD)
        return FALSE;
    res = parser->state == OK && ft_pop(parser, MODE_DONE);
	ft_destroy(parser);
    return (res);
}
