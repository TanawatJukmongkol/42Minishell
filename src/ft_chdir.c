/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:38:31 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/12 20:02:18 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

char	*ft_chdir(char *path, t_stackheap *mem)
{
	char	*real;

	real = ft_realpath(path, NULL, mem);
	if (!real)
		return (NULL);
	if (!chdir(real))
		return (NULL);
	return (real);
}
