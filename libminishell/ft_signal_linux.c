/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_linux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:31:44 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/09 21:26:34 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

int	ft_sig_init(t_sigaction *s, int flag, void (*hand)(int),\
				 void (*sact)(int, siginfo_t *, void *))
{
	s->sa_flags = flag;
	if (sigemptyset(&s->sa_mask) == -1)
		return (perror(ERR_MSG), -1);
	s->sa_handler = hand;
	s->sa_sigaction = sact;
	return (0);
}
