/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_mac.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:31:44 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/17 15:27:24 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

int	init_mask(t_sigaction *sig1, t_sigaction *sig2)
{
	if (sigemptyset(&sig1->sa_mask) == -1)
		return (0);
	if (sigemptyset(&sig2->sa_mask) == -1)
		return (0);
	sig1->sa_flags = SA_RESTART;
	sig1->__sigaction_u.__sa_handler = sig_int;
	sig2->sa_flags = SA_RESTART;
	sig2->__sigaction_u.__sa_handler = sig_quit;
	return (1);
}

int	ft_signal(void)
{
	t_sigaction	sig1;
	t_sigaction	sig2;

	if (!init_mask(&sig1, &sig2))
		return (0);
	if (sigaction(SIGINT, &sig1, NULL) == -1)
		return (0);
	if (sigaction(SIGQUIT, &sig2, NULL) == -1)
		return (0);
	return (1);
}
