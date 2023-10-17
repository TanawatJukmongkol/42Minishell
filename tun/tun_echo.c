/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/17 18:56:15 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

// WORK

// static void	sb_print_ngong(char *str, int ngong)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i] != 0)
// 	{
// 		if (str[i] == '$' && str[i + 1] == '?')
// 		{
// 			printf("%d", ngong);
// 			i++;
// 		}
// 		else
// 			printf("%c", str[i]);
// 		i++;
// 	}
// }

int	tun_echo(char **av, t_exec *exe)
{
	size_t	len;
	int		i;
	int		flag;

	(void)exe;
	if (av[1] == NULL)
		return (0);
	len = ft_strlen(av[1]);
	flag = ft_strncmp(av[1], "-n", len + 1);
	i = ft_ternary(flag == 0, 2, 1);
	while (av[i] != NULL)
	{
		printf("%s", av[i]);
		if (av[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (flag != 0)
		printf("\n");
	return (0);
}
