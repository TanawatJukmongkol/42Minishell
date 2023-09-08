/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:38:31 by tjukmong          #+#    #+#             */
/*   Updated: 2023/08/24 05:11:32 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

char	*ft_chdir(char *path)
{
	char	*real;

	real = ft_realpath(path, NULL);
	if (!chdir(real))
		return (NULL);
	return (real);
}
