/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/16 01:53:59 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

// WORK

static void	sb_print_ngong(char *str, int ngong)
{
	size_t	i;

	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			printf("%d", ngong);
			i++;
		}
		else
			printf("%c", str[i]);
		i++;
	}
}

int	tun_echo(char **av, t_exec *exe)
{
	size_t	len;
	int		i;
	int		flag;

	if (av[1] == NULL)
		return (0);
	len = ft_strlen(av[1]);
	flag = ft_strncmp(av[1], "-n", len + 1);
	i = ft_ternary(flag == 0, 2, 1);
	while (av[i] != NULL)
	{
		if (ft_strnstr(av[i], "$?", ft_strlen(av[i])) != NULL)
			sb_print_ngong(av[i], exe->_info->_ngong);
		else
			printf("%s", av[i]);
		if (av[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (flag != 0)
		printf("\n");
	return (0);
}
