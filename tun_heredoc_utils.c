/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_heredoc_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/18 01:55:28 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

int	tun_delimeter(char *del, char *line, size_t del_len, size_t len)
{
	if (del_len != len)
		return (0);
	if (ft_strncmp(del, line, len) != 0)
		return (0);
	return (1);
}

// get pointer of last delimeter for finding it

char	*tun_last_delimeter(t_token_stream subset)
{
	char	*str;

	str = NULL;
	while (subset.begin != NULL)
	{
		if (subset.begin->type == __here_doc)
			str = subset.begin->value;
		subset.begin = subset.begin->next;
	}
	return (str);
}

int	tun_dup_heredoc(int fd1, int fd2)
{
	int	err;

	if (fd1 < 0 || fd2 < 0)
		return (0);
	err = tun_dup2(fd1, fd2);
	return (err);
}
