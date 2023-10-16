/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:48:03 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/16 12:49:27 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

int	ft_clear_main(t_main *info, int status)
{
	free(info->_home);
	ft_tokenfree(&info->_token);
	ft_clear_envp(info->_envp.env);
	return (status);
}
