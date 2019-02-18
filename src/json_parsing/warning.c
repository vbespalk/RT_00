
#include "json.h"

static void	ft_get_line_symbol(char *content, char *attr, int *line, int *symb)
{
	int		i;
	int		len;

	*line = 1;
	*symb = 0;
	i = -1;
	len = (int)(attr - content + 1);
	while (++i < len)
	{
		++(*symb);
		if (content[i] == '\n')
		{
			++(*line);
			*symb = 0;
		}
	}
}

static char *ft_get_dt_str(t_datatype datatype)
{
	char	*dt;

	if (datatype == DT_COLOR)
		dt = ft_strdup("     color");
	else if (datatype == DT_STRING)
		dt = ft_strdup("    string");
	else if (datatype == DT_POINT)
		dt = ft_strdup("     point");
	else if (datatype == DT_FLOAT)
		dt = ft_strdup("     float");
	else
		dt = ft_strdup("0 - 1 coef");
	return (dt);
}

static char	*ft_get_line_ptr(char *content)
{
	char 		*line_ptr;
	size_t		len;

	len = 0;
	while (content[len] && content[len] != '\n')
		++len;
	line_ptr = (char *)ft_smemalloc(len + 1, "ft_check_syntax");
	line_ptr[len] = 0;
	ft_memmove(line_ptr, content - len, len);
	return (line_ptr);
}

void		ft_parse_warning(char *content, char *attr, t_datatype datatype)
{
	int		line;
	int		symbol;
	char	*dt;
	char 	*line_ptr;
	int		i;

	ft_get_line_symbol(content, attr, &line, &symbol);
	dt = ft_get_dt_str(datatype);
	line_ptr = ft_get_line_ptr(attr - symbol + 1);
	ft_printf("PARSE WARNING at line %4d: data type mismatch", line);
	ft_printf(" - expected %s, value set to default: <<%s>>\n", dt, line_ptr);
	write(1, "                                                  ", 50);
	write(1, "                                            ", 44);
	i = -1;
	while (++i < symbol - 1)
		write(1, (line_ptr[i] == '\t') ? "\t" : " ", 1);
	write(1, "^", 1);
	free(line_ptr);
	free(dt);
}
