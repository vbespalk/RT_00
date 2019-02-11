
#include "json.h"

static void		ft_syntax_error(char *content, int line, int symbol)
{
	char 		*line_ptr;
	size_t		len;

	len = 0;
	while (content[len] && content[len] != '\n')
		++len;
	line_ptr = (char *)ft_smemalloc(len + 1, "ft_check_syntax");
	line_ptr[len] = 0;
	memmove(line_ptr, content - len, len);
	ft_printf("SYNTAX ERROR at line %4d : <<%s>>\n", line, line_ptr);
	ft_printf("                              ");
	for (int i = 0; i < symbol - 1; ++i)
		ft_printf("%c", line_ptr[i] == '\t' ? '\t' : ' ');
	ft_printf("^");
	free(line_ptr);
	ft_error("scene file is invalid");
}

void			ft_check_syntax(char *content)
{
	t_checker	checker;
	int			line;
	int			symbol;

	checker = ft_checkernew(OBJ_DEPTH);
	line = 1;
	symbol = 0;
	while (*content && ft_check_char(checker, *content))
	{
		if (*content == '\n')
		{
			++line;
			symbol = 0;
		}
		++symbol;
		++content;
	}
	content = content - symbol + 1;
	if (!ft_check_done(checker))
		ft_syntax_error(content, line, symbol);
}
