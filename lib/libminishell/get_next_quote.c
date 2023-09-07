
#include "libminishell.h"

char	*get_next_qoute(char *str, char *match, int single)
{
	int		q;
	int		dbq;

	q = 0;
	dbq = 0;
	while (*str)
	{
		if (single && *str == '\"' && *str != '\'')
			dbq = !dbq;
		if (*str == '\'' && *str != '\"')
			q = !q;
		if (!ft_strncmp(str, match, ft_strlen(
						match)) && !q && !dbq)
			break ;
		str++;
	}
	return (str);
}

