/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_mac.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:31:44 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/09 21:27:56 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

int	ft_sig_init(t_sigaction *s, int flag, void (*hand)(int),\
				 void (*sact)(int, siginfo_t *, void *))
{
	s->sa_flags = flag;
	if (sigemptyset(&s->sa_mask) == -1)
		return (perror(ERR_MSG), -1);
	s->__sigaction_u.__sa_handler = hand;
	s->__sigaction_u.__sa_sigaction = sact;
	return (0);
}
