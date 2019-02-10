
#include "json.h"



static int ascii_class[128] = {
/*
    This array maps the 128 ASCII characters into character classes.
    The remaining Unicode characters should be mapped to C_ETC.
    Non-whitespace control characters are errors.
*/
    _,      _,      _,      _,      _,      _,      _,      _,
    _,      C_WHITE, C_WHITE, _,      _,      C_WHITE, _,      _,
    _,      _,      _,      _,      _,      _,      _,      _,
    _,      _,      _,      _,      _,      _,      _,      _,

    C_SPACE, C_ETC,   C_QUOTE, C_ETC,   C_ETC,   C_ETC,   C_ETC,   C_ETC,
    C_ETC,   C_ETC,   C_ETC,   C_PLUS,  C_COMMA, C_MINUS, C_POINT, C_SLASH,
    C_ZERO,  C_DIGIT, C_DIGIT, C_DIGIT, C_DIGIT, C_DIGIT, C_DIGIT, C_DIGIT,
    C_DIGIT, C_DIGIT, C_COLON, C_ETC,   C_ETC,   C_ETC,   C_ETC,   C_ETC,

    C_ETC,   C_ABCDF, C_ABCDF, C_ABCDF, C_ABCDF, C_E,     C_ABCDF, C_ETC,
    C_ETC,   C_ETC,   C_ETC,   C_ETC,   C_ETC,   C_ETC,   C_ETC,   C_ETC,
    C_ETC,   C_ETC,   C_ETC,   C_ETC,   C_ETC,   C_ETC,   C_ETC,   C_ETC,
    C_ETC,   C_ETC,   C_ETC,   C_LSQRB, C_BACKS, C_RSQRB, C_ETC,   C_ETC,

    C_ETC,   C_LOW_A, C_LOW_B, C_LOW_C, C_LOW_D, C_LOW_E, C_LOW_F, C_ETC,
    C_ETC,   C_ETC,   C_ETC,   C_ETC,   C_LOW_L, C_ETC,   C_LOW_N, C_ETC,
    C_ETC,   C_ETC,   C_LOW_R, C_LOW_S, C_LOW_T, C_LOW_U, C_ETC,   C_ETC,
    C_ETC,   C_ETC,   C_ETC,   C_LCURB, C_ETC,   C_RCURB, C_ETC,   C_ETC
};


/*
    The state codes.
*/
enum states {
    GO,  /* start    */
    OK,  /* ok       */
    OB,  /* object   */
    KE,  /* key      */
    CO,  /* colon    */
    VA,  /* value    */
    AR,  /* array    */
    ST,  /* string   */
    ES,  /* escape   */
    U1,  /* u1       */
    U2,  /* u2       */
    U3,  /* u3       */
    U4,  /* u4       */
    MI,  /* minus    */
    ZE,  /* zero     */
    IN,  /* integer  */
    FR,  /* fraction */
    FS,  /* fraction */
    E1,  /* e        */
    E2,  /* ex       */
    E3,  /* exp      */
    T1,  /* tr       */
    T2,  /* tru      */
    T3,  /* true     */
    F1,  /* fa       */
    F2,  /* fal      */
    F3,  /* fals     */
    F4,  /* false    */
    N1,  /* nu       */
    N2,  /* nul      */
    N3,  /* null     */
    NR_STATES
};


static int state_transition_table[NR_STATES][NR_CLASSES] = {
/*
    The state transition table takes the current state and the current symbol,
    and returns either a new state or an action. An action is represented as a
    negative number. A JSON text is accepted if at the end of the text the
    state is OK and if the mode is MODE_DONE.
                 white                                      1-9                                   ABCDF  etc
             space |  {  }  [  ]  :  ,  "  \  /  +  -  .  0  |  a  b  c  d  e  f  l  n  r  s  t  u  |  E  |*/
/*start  GO*/ {GO,GO,-6,_,-5,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
/*ok     OK*/ {OK,OK,_,-8,_,-7,_,-3,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
/*object OB*/ {OB,OB,_,-9,_,_,_,_,ST,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
/*key    KE*/ {KE,KE,_,_,_,_,_,_,ST,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
/*colon  CO*/ {CO,CO,_,_,_,_,-2,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
/*value  VA*/ {VA,VA,-6,_,-5,_,_,_,ST,_,_,_,MI,_,ZE,IN,_,_,_,_,_,F1,_,N1,_,_,T1,_,_,_,_},
/*array  AR*/ {AR,AR,-6,_,-5,-7,_,_,ST,_,_,_,MI,_,ZE,IN,_,_,_,_,_,F1,_,N1,_,_,T1,_,_,_,_},
/*string ST*/ {ST,_,ST,ST,ST,ST,ST,ST,-4,ES,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST},
/*escape ES*/ {_,_,_,_,_,_,_,_,ST,ST,ST,_,_,_,_,_,_,ST,_,_,_,ST,_,ST,ST,_,ST,U1,_,_,_},
/*u1     U1*/ {_,_,_,_,_,_,_,_,_,_,_,_,_,_,U2,U2,U2,U2,U2,U2,U2,U2,_,_,_,_,_,_,U2,U2,_},
/*u2     U2*/ {_,_,_,_,_,_,_,_,_,_,_,_,_,_,U3,U3,U3,U3,U3,U3,U3,U3,_,_,_,_,_,_,U3,U3,_},
/*u3     U3*/ {_,_,_,_,_,_,_,_,_,_,_,_,_,_,U4,U4,U4,U4,U4,U4,U4,U4,_,_,_,_,_,_,U4,U4,_},
/*u4     U4*/ {_,_,_,_,_,_,_,_,_,_,_,_,_,_,ST,ST,ST,ST,ST,ST,ST,ST,_,_,_,_,_,_,ST,ST,_},
/*minus  MI*/ {_,_,_,_,_,_,_,_,_,_,_,_,_,_,ZE,IN,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
/*zero   ZE*/ {OK,OK,_,-8,_,-7,_,-3,_,_,_,_,_,FR,_,_,_,_,_,_,E1,_,_,_,_,_,_,_,_,E1,_},
/*int    IN*/ {OK,OK,_,-8,_,-7,_,-3,_,_,_,_,_,FR,IN,IN,_,_,_,_,E1,_,_,_,_,_,_,_,_,E1,_},
/*frac   FR*/ {_,_,_,_,_,_,_,_,_,_,_,_,_,_,FS,FS,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
/*fracs  FS*/ {OK,OK,_,-8,_,-7,_,-3,_,_,_,_,_,_,FS,FS,_,_,_,_,E1,_,_,_,_,_,_,_,_,E1,_},
/*e      E1*/ {_,_,_,_,_,_,_,_,_,_,_,E2,E2,_,E3,E3,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
/*ex     E2*/ {_,_,_,_,_,_,_,_,_,_,_,_,_,_,E3,E3,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
/*exp    E3*/ {OK,OK,_,-8,_,-7,_,-3,_,_,_,_,_,_,E3,E3,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
/*tr     T1*/ {_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,T2,_,_,_,_,_,_},
/*tru    T2*/ {_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,T3,_,_,_},
/*true   T3*/ {_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,OK,_,_,_,_,_,_,_,_,_,_},
/*fa     F1*/ {_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,F2,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
/*fal    F2*/ {_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,F3,_,_,_,_,_,_,_,_},
/*fals   F3*/ {_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,F4,_,_,_,_,_},
/*false  F4*/ {_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,OK,_,_,_,_,_,_,_,_,_,_},
/*nu     N1*/ {_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,N2,_,_,_},
/*nul    N2*/ {_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,N3,_,_,_,_,_,_,_,_},
/*null   N3*/ {_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,OK,_,_,_,_,_,_,_,_}
};


/*
    These modes can be pushed on the stack.
*/
enum modes {
    MODE_ARRAY,
    MODE_DONE,
    MODE_KEY,
    MODE_OBJECT
};

static void
destroy(t_checker jc)
{
/*
    Delete the t_checker object.
*/
    jc->valid = 0;
    free((void*)jc->stack);
    free((void*)jc);
}


static int
reject(t_checker jc)
{
/*
    Delete the t_checker object.
*/
    destroy(jc);
    return FALSE;
}


static int
push(t_checker jc, int mode)
{
/*
    Push a mode onto the stack. Return false if there is overflow.
*/
    jc->top += 1;
    if (jc->top >= jc->depth) {
        return FALSE;
    }
    jc->stack[jc->top] = mode;
    return TRUE;
}


static int
pop(t_checker jc, int mode)
{
/*
    Pop the stack, assuring that the current mode matches the expectation.
    Return false if there is underflow or if the modes mismatch.
*/
    if (jc->top < 0 || jc->stack[jc->top] != mode) {
        return FALSE;
    }
    jc->top -= 1;
    return TRUE;
}


t_checker
ft_checkernew(int depth)
{
/*
    ft_checkernew starts the checking process by constructing a t_checker
    object. It takes a depth parameter that restricts the level of maximum
    nesting.
    To continue the process, call JSON_checker_char for each character in the
    JSON text, and then call JSON_checker_done to obtain the final result.
    These functions are fully reentrant.
    The t_checker object will be deleted by ft_check_done.
    ft_check_char will delete the t_checker object if it sees an error.
*/
    t_checker jc = (t_checker)malloc(sizeof(struct JSON_checker_struct));
    jc->valid = GOOD;
    jc->state = GO;
    jc->depth = depth;
    jc->top = -1;
    jc->stack = (int*)calloc(depth, sizeof(int));
    push(jc, MODE_DONE);
    return jc;
}


int
ft_check_char(t_checker parser, int c)
{
/*
    After calling ft_checkernew, call this function for each character (or
    partial character) in your JSON text. It can accept UTF-8, UTF-16, or
    UTF-32. It returns TRUE if things are looking ok so far. If it rejects the
    text, it destroys the t_checker object and returns false.
*/
    int next_class, next_state;
/*
    Determine the character's class.
*/
    if (parser->valid != GOOD) {
        return FALSE;
    }
    if (c < 0) {
        return reject(parser);
    }
    if (c >= 128) {
        next_class = C_ETC;
    } else {
        next_class = ascii_class[c];
        if (next_class <= _) {
            return reject(parser);
        }
    }
/*
    Get the next state from the state transition table.
*/
    next_state = state_transition_table[parser->state][next_class];
    if (next_state >= 0) {
/*
    Change the state.
*/
        parser->state = next_state;
/*
    Or perform one of the actions.
*/
    } else {
        switch (next_state) {
/* empty } */
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
/*
    A comma causes a flip from object mode to key mode.
*/
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
/*
    A colon causes a flip from key mode to object mode.
*/
            if (!pop(parser, MODE_KEY) || !push(parser, MODE_OBJECT)) {
                return reject(parser);
            }
            parser->state = VA;
            break;
/*
    Bad action.
*/
        default:
            return reject(parser);
        }
    }
    return TRUE;
}


int
ft_check_done(t_checker parser)
{
/*
    The ft_check_done function should be called after all of the characters
    have been processed, but only if every call to ft_check_char returned
    true. This function deletes the t_checker and returns true if the JSON
    text was accepted.
*/
    if (parser->valid != GOOD) {
        return FALSE;
    }
    int result = parser->state == OK && pop(parser, MODE_DONE);
    destroy(parser);
    return result;
}







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
