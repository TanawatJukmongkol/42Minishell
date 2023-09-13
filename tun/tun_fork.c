/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/14 02:42:32 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

int	tun_fork(const char *msg)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		perror(msg);
	return (pid);
}

int	tun_waitpid(int pid, int *stat, int option, const char *msg)
{
	int	id;

	id = waitpid(pid, stat, option);
	if (id == -1)
		return (perror(msg), -1);
	return (id);
}