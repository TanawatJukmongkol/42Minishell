/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dynamic_prompt.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 00:07:08 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/18 01:58:45 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

char	*ft_dynamic_prompt(t_main *m)
{
	char	*exit_stat;
	char	*base;
	char	*head;
	char	*tmp1;
	char	*tmp2;

	base = "\x1b[33m";
	exit_stat = "\x1b[36m?";
	head = "\x1b[32m $\x1b[0m ";
	tmp1 = ft_getcwd();
	base = ft_strjoin(base, tmp1);
	free(tmp1);
	exit_stat = ft_strjoin(base, exit_stat);
	free(base);
	tmp2 = ft_itoa(m->_ngong);
	tmp1 = ft_strjoin(exit_stat, tmp2);
	free(exit_stat);
	free(tmp2);
	head = ft_strjoin(tmp1, head);
	free(tmp1);
	return (head);
}
