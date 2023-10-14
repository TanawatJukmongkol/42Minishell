/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/14 04:56:50 by tponutha         ###   ########.fr       */
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
