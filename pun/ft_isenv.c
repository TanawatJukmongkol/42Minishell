/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:46:00 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/12 17:46:01 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

int	ft_isenv(int c)
{
	if (ft_isalnum(c))
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

