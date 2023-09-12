/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:45:00 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/12 17:45:45 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

char	*get_next_qoute(char *str, char *match, int single)
{
	int		q;
	int		dbq;

	q = 0;
	dbq = 0;
	while (*str)
	{
		if (single && !q && *str == '\"')
			dbq = !dbq;
		if (!dbq && *str == '\'')
			q = !q;
		if (!ft_strncmp(str, match, ft_strlen(
					match)) && !q && (!dbq || single > 1))
			break ;
		str++;
	}
	return (str);
}

