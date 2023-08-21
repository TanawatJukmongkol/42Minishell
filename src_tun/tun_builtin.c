/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/08/22 00:04:39 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

static int	sb_chdir(char **av, t_exec *info)
{
	char	here[PATH_MAX];

	if (getcwd(here, PATH_MAX) == NULL)
	{
		perror("minishell: cd:");
		return (1);
	}
	ft_strlcpy(info->current_path, here, PATH_MAX);
	// set $PWD
	return (0);
}

static int	sb_echo(char **av, t_exec *info)
{
	size_t	len;
	int		i;
	int		flag;

	if (av[1] == NULL)
		return (0);
	len = ft_strlen(av[1]);
	flag = ft_strncmp(av[1], "-n", len + 1);
	i = ft_ternary(flag, 2, 1);
	while (av[i] != NULL)
	{
		if (av[i + 1] != NULL)
			printf("%s ", av[i]);
		else
			printf("%s", av[i]);
		i++;
	}
	if (flag != 0)
		printf("\n");
	return (0);
}

// TODO: pwd kinda don't use getcwd & $PWD

/*
RETURN VALUE
-1			: cmd isn't built-in
0			: no error
positive	: error
*/

int	tun_builin_handler(char *cmd, char **av, t_exec *info)
{
	size_t	size;
	int		err;

	err = -1;
	size = ft_strlen(cmd);
	if (ft_strncmp(cmd, "echo", size) == 0)
		err = sb_echo(av, info);
	else if (ft_strncmp(cmd, "pwd", size) == 0)
		err = 0 & printf("%s\n", info->current_path);
	else if (ft_strncmp(cmd, "cd", size) == 0)
		err = 0;
	else if (ft_strncmp(cmd, "export", size) == 0)
		err = 0;
	else if (ft_strncmp(cmd, "unset", size) == 0)
		err = 0;
	else if (ft_strncmp(cmd, "exit", size) == 0)
		ft_exit(info->mem, 0);
	return (err);
}