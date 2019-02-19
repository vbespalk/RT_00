
#include "rt.h"

static char	*ft_read(char *filename)
{
	int		fd;

	if ((fd = open(filename, O_RDONLY)) < 0)
		ft_error("cannot open file");
	if ((read(fd, NULL, 0)) < 0)
		ft_error("cannot read file");
	return (ft_readfile(filename));
}

t_scene		*ft_parse_json(char *filename)
{
	char	*content;
	t_scene	*scn;

	content = ft_read(filename);
	scn = ft_scenenew();
	ft_check_syntax(content);
	//ft_parse_content(scn, content);
	return (scn);
}
