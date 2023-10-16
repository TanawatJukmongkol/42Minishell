/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:48:03 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/17 00:27:24 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

int	ft_clear_main(t_main *info, int status)
{
	free(info->_home);
	ft_tokenfree(&info->_token);
	ft_clear_envp(info->_envp.env);
	// rl_clear_history();
	return (status);
}
