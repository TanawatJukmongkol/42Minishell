/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenfree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:48:03 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/12 19:11:13 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pun.h"

void	ft_tokenfree(t_token_stream *s)
{
	t_token	*tmp;

	while (s->begin)
	{
		tmp = s->begin->next;
		free(s->begin->value);
		free(s->begin);
		s->begin = tmp;
	}
}
