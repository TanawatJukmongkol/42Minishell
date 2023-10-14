/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 12:12:52 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/05 15:26:08 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// loops through string *s, and run callback f that returns computed
// characters, with unsigned int as the index, and the current
// character at sed index of string *s.

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	indx;

	if (!s || !f)
		return (NULL);
	str = malloc(ft_strlen(s) + 1);
	if (!str)
		return (NULL);
	indx = 0;
	while (s[indx])
	{
		str[indx] = f(indx, s[indx]);
		indx++;
	}
	str[indx] = '\0';
	return (str);
}
