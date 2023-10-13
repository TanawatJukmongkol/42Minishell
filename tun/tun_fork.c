/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/13 14:13:11 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

int	tun_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		perror("minishell: fork");
	return (pid);
}

int	tun_waitpid(int pid, int *stat, int option)
{
	int	id;

	if (pid == BUILTIN_PID)
		return (0);
	id = waitpid(pid, stat, option);
	if (id == -1)
		return (-1);
	return (id);
}

int	tun_redirct(int *fdes, int len, int std, int isok)
{
	if (isok == 0)
		return (0);
	if (fdes == NULL)
		return (len != -1);
	len--;
	while (len > 0 && fdes[len] != std)
	{
		if (tun_dup2(fdes[len], fdes[len - 1]) == -1)
			return (0);
		len--;
	}
	return (1);
}