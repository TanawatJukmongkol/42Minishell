/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 02:08:33 by tponutha          #+#    #+#             */
/*   Updated: 2023/10/14 04:56:54 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

int	tun_redirct(int *fdes, int len, int std, int isok)
{
	if (fdes == NULL)
		return (len != -1);
	if (isok == 0)
		return (0);
	len--;
	while (len > 0 && fdes[len] != std)
	{
		if (tun_dup2(fdes[len], fdes[len - 1]) == -1)
			return (0);
		len--;
	}
	return (1);
}
