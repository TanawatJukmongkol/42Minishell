/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_perror.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 02:08:33 by tponutha          #+#    #+#             */
/*   Updated: 2023/10/12 14:42:11 by tponutha         ###   ########.fr       */
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
	return ;
}