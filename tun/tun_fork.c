/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/16 04:11:25 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

int	tun_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("minishell: fork");
	return (pid);
}

int	tun_waitpid(pid_t pid, int *stat, int option)
{
	int	id;

	id = waitpid(pid, stat, option);
	if (id == -1)
		return (-1);
	return (id);
}
