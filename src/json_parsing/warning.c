
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

	if (datatype == DT_POINT)
		dt = ft_strdup("POINT");
	else if (datatype == DT_CAMERA)
		dt = ft_strdup("CAMERA");
	else if (datatype == DT_OBJECT_ARR)
		dt = ft_strdup("OBJECT ARRAY");
	else if (datatype == DT_LIGHT_ARR)
		dt = ft_strdup("LIGHT ARRAY");
	else if (datatype == DT_STRING)
		dt = ft_strdup("STRING");
	else if (datatype == DT_COLOR)
		dt = ft_strdup("COLOR");
	else if (datatype == DT_FLOAT)
		dt = ft_strdup("FLOAT");
	else
		dt = ft_strdup("0 - 1 COEF");
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
	ft_memmove(line_ptr, content, len);
	return (line_ptr);
}

static void	ft_put_space(size_t	len)
{
	char	*space;

	space = ft_strnew((size_t)len, ' ');
	write(1, space, len);
	free(space);
}

void		ft_parse_warning_datatype
				(char *content, char *attr, t_datatype datatype)
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
	ft_printf(", expected %s, value set to default: %s\n", dt, line_ptr);
	ft_put_space(81 + ft_strlen(dt));
	i = -1;
	free(dt);
	dt = (char *)ft_smemalloc(sizeof(char) * (symbol + 1), "ft_parse_warning");
	while (++i < symbol - 1)
		dt[i] = (char)((line_ptr[i] == '\t') ? '\t' : ' ');
	dt[i] = '^';
	dt[i + 1] = '\n';
	write(1, dt, (size_t)symbol + 1);
	free(line_ptr);
	free(dt);
}
