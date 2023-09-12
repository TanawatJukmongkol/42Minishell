/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:54:46 by tponutha          #+#    #+#             */
/*   Updated: 2023/09/12 19:11:20 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pun.h"

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
						match)) && !q && !dbq)
			break ;
		str++;
	}
	return (str);
}

