/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/10 08:36:45 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

int	tun_open(const char *path, int oflag, mode_t mode)
{
	int	fd;

	fd = open(path, oflag, mode);
	if (fd == -1)
		perror(ERR_MSG);
	return (fd);
}

void	tun_close(int fd)
{
	int	err;

	if (fd == -1)
		return ;
	err = close(fd);
	if (err == -1)
		perror(ERR_MSG);
}

int	tun_dup2(int fd1, int fd2)
{
	int	err;

	err = dup2(fd1, fd2);
	if (err == -1)
		perror(ERR_MSG);
	return (err);
}

int	tun_pipe(int fdes[2])
{
	int	err;
	
	err = pipe(fdes);
	if (err == -1)
		perror(ERR_MSG);
	return (err);
}

void	tun_close_files(int *fdes, int n)
{
	int	i;

	i = 0;
	if (fdes == NULL)
		return ;
	while (i < n)
	{
		if (fdes[i] > 2)
			close(fdes[i]);
		i++;
	}
	free(fdes);
}