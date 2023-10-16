/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_mac.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:31:44 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/16 13:08:52 by tponutha         ###   ########.fr       */
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

void	sig_quit(int signum)
{
	if (signum == SIGQUIT)
		return ;
}

void	sig_int(int signum)
{
	if (signum == SIGINT)
	{
		rl_redisplay();
	}
}

int	ft_signal(void)
{
	t_sigaction	sig1;
	t_sigaction	sig2;

	if (sigemptyset(&sig1.sa_mask) == -1)
		return (0);
	if (sigemptyset(&sig2.sa_mask) == -1)
		return (0);
	sig1.sa_flags = SA_RESTART;
	sig1.__sigaction_u.__sa_handler = sig_int;
	sig2.sa_flags = SA_RESTART;
	sig2.__sigaction_u.__sa_handler = sig_quit;
	if (sigaction(SIGINT, &sig1, NULL) == -1)
		return (0);
	if (sigaction(SIGQUIT, &sig2, NULL) == -1)
		return (0);
	return (1);
}