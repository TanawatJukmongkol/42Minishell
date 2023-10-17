/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sorttable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 23:26:04 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/17 23:50:09 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

size_t	table_len(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	swap_address(char **a1, char **a2)
{
	char	*tmp;

	tmp = *a1;
	*a1 = *a2;
	*a2 = tmp;
}

void	ft_sorttable(char **tab)
{
	size_t	tab_len;
	size_t	i;
	size_t	j;
	size_t	strlen_a;
	size_t	strlen_b;

	i = 0;
	tab_len = table_len(tab);
	while (i < tab_len)
	{
		j = 0;
		while (j < tab_len - 1)
		{
			strlen_a = ft_strlen(tab[j]);
			strlen_b = ft_strlen(tab[j + 1]);
			if (strlen_a < strlen_b)
				strlen_b = strlen_a;
			if (ft_strncmp(tab[j], tab[j + 1], strlen_b) > 0)
				swap_address(tab + j, tab + j + 1);
			j++;
		}
		i++;
	}
}
