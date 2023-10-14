/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenfree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:48:03 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/09 00:19:26 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

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
