/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_perror.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 02:08:33 by tponutha          #+#    #+#             */
/*   Updated: 2023/10/13 14:11:37 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

void	tun_cmd_perror(t_exec *exe, char *err)
{
	char	*first;
	char	*second;
	char	*third;

	first = "minishell: ";
	second = ft_strjoin(first, exe->argv[0]);
	if (second == NULL)
		return ;
	third = ft_strjoin(second, err);
	free(second);
	if (third == NULL)
		return ;
	ft_putstr_fd(third, STDERR_FILENO);
	free(third);
}

void	tun_file_perror(t_exec *exe)
{
	char	*first;
	char	*second;
	char	*third;
	char	*final;
	char	*err;

	first = "minishell: ";
	second = ft_strjoin(first, exe->argv[0]);
	if (second == NULL)
		return ;
	err = strerror(errno);
	third = ft_strjoin(second, ": ");
	free(second);
	if (third == NULL)
		return ;
	second = ft_strjoin(third, err);
	free(third);
	if (second == NULL)
		return ;
	final = ft_strjoin(second, "\n");
	free(second);
	if (final != NULL)
		ft_putstr_fd(final, STDERR_FILENO);
	free(final);
}

void	tun_open_perror(const char *path)
{
	char	*first;
	char	*err;
	char	*second;
	char	*third;
	char	*final;

	first = "minishell: ";
	second = ft_strjoin(first, path);
	if (second == NULL)
		return ;
	err = strerror(errno);
	third = ft_strjoin(second, ": ");
	free(second);
	if (third == NULL)
		return ;
	second = ft_strjoin(third, err);
	free(third);
	if (second == NULL)
		return ;
	final = ft_strjoin(second, "\n");
	free(second);
	if (final != NULL)
		ft_putstr_fd(final, STDERR_FILENO);
	free(final);
}
