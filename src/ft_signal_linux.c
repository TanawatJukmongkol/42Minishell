/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_linux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:31:44 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/16 08:49:13 by tponutha         ###   ########.fr       */
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

void	sig_quit(int signum)
{
	if (signum == SIGQUIT)
		return ;
}

void	sig_int(int signum)
{
	(void)signum;
	rl_redisplay();
}

int	ft_signal(void)
{
	t_sigaction	sig1;
	t_sigaction	sig2;

	printf("WORK\n");
	if (sigemptyset(&sig1.sa_mask) == -1)
		return (0);
	if (sigemptyset(&sig2.sa_mask) == -1)
		return (0);
	sig1.sa_flags = SA_NOCLDWAIT;
	sig1.sa_handler = sig_int;
	sig1.sa_sigaction = NULL;
	sig2.sa_flags = SA_NOCLDWAIT;
	sig2.sa_handler = sig_quit;
	sig2.sa_sigaction = NULL;
	if (sigaction(SIGINT, &sig1, NULL) == -1)
		return (0);
	if (sigaction(SIGQUIT, &sig2, NULL) == -1)
		return (0);
	return (1);
}