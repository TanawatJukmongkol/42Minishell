/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 20:32:06 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/05 15:22:50 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// get how many words are there, that is not the deluminator.
// ft_split("  Hello, world!   ", ' '); -> 2 words, hence the length of 2.
static int	ft_splitlen(char const *s, char c)
{
	char	*str;
	int		len;
	int		flag;

	str = (char *)s;
	len = 0;
	flag = 0;
	while (*str)
	{
		if (*str != c && !flag)
		{
			len++;
			flag = 1;
		}
		else if (*str == c && flag)
			flag = 0;
		str++;
	}
	return (len);
}

// Free the whole 2D array if failed to malloc.
static void	ft_free_split(void *box)
{
	int		i;
	char	**s;

	i = 0;
	s = (char **)box;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

// Malloc and sets the 2d array's value, if fails free all.
static char	**ft_put_table(char **res, char *str, char c, int len)
{
	int		a;
	int		b;

	a = 0;
	b = 0;
	while (a < len)
	{
		if (*str && *str != c)
			b++;
		else if (b != 0)
		{
			res[a] = malloc((b + 1) * sizeof(char));
			if (!res[a])
				return (ft_free_split(res), NULL);
			ft_memcpy(res[a], str - b, b);
			res[a][b] = '\0';
			a++;
			b = 0;
		}
		str++;
	}
	return (res);
}

// malloc the 2D array, with size of split len, then malloc the table.
char	**ft_split(char const *s, char c)
{
	char	**res;
	char	*str;
	int		len;

	if (!s)
		return (NULL);
	str = (char *)s;
	len = ft_splitlen(s, c);
	res = malloc((len + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	res[len] = NULL;
	return (ft_put_table(res, str, c, len));
}
