/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_heredoc_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/16 03:07:05 by tponutha         ###   ########.fr       */
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

int	tun_find_last_heredoc(int *infile, int in_len)
{
	int	i;
	int	pos;

	i = 0;
	pos = 0;
	while (i < in_len)
	{
		if (infile[i] == STDIN_FILENO)
			pos = i;
		i++;
	}
	return (pos);
}
