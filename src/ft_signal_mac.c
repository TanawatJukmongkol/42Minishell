/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_mac.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:31:44 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/17 00:42:44 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

void	sig_quit(int signum)
{
	if (signum == SIGQUIT)
	{
		rl_redisplay();
	}
}

void	sig_int(int signum)
{
	if (signum == SIGINT)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_chld(int signum)
{
	if (signum == SIGCHLD)
		printf("\33[2K\r\b");
}

int	ft_signal(void)
{
	t_sigaction	sig1;
	t_sigaction	sig2;
	t_sigaction	sig3;

	if (sigemptyset(&sig1.sa_mask) == -1)
		return (0);
	if (sigemptyset(&sig2.sa_mask) == -1)
		return (0);
	if (sigemptyset(&sig2.sa_mask) == -1)
		return (0);
	sig1.sa_flags = SA_RESTART;
	sig1.__sigaction_u.__sa_handler = sig_int;
	sig2.sa_flags = SA_RESTART;
	sig2.__sigaction_u.__sa_handler = sig_quit;
	sig3.sa_flags = SA_RESTART | SA_NOCLDSTOP;
	sig3.__sigaction_u.__sa_handler = sig_chld;
	if (sigaction(SIGINT, &sig1, NULL) == -1)
		return (0);
	if (sigaction(SIGQUIT, &sig2, NULL) == -1)
		return (0);
	if (sigaction(SIGCHLD, &sig3, NULL) == -1)
		return (0);
	return (1);
}
