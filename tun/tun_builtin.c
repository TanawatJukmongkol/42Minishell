/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/14 03:24:39 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

// static int	sb_chdir(char **av, t_main *info)
// {
// 	char	here[PATH_MAX];

// 	if (getcwd(here, PATH_MAX) == NULL)
// 	{
// 		// perror("minishell: cd:");
// 		return (1);
// 	}
// 	ft_strlcpy(info->_path, here, PATH_MAX);
// 	// set $PWD
// 	return (0);
// }

static int	sb_echo(char **av)
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
		printf("%s", av[i]);
		if (av[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (flag != 0)
		printf("\n");
	return (0);
}

static int	sb_cd(char **av, t_main *info)
{
	char	*dir;
	size_t	len;

	len = 0;
	while (av[len])
		len++;
	if (len > 2)
		return (1);
	// if (len == 0)
	// 	dir = dir;
	dir = ft_chdir(av[1], &info->_mem);
	if (dir == NULL)
		return (1);
	if (ft_editenv("PWD", &info->_envp) == NULL)
		return (perror("minishell : export :"), 1); // TODO : write perror here
	if (ft_editenv("OLDPWD", &info->_envp) == NULL)
		return (perror("minishell : export :"), 1); // TODO : write perror here
	return (0);
}

// TODO: pwd kinda don't use getcwd & $PWD

static int	sb_export(char **av, t_main *info)
{
	size_t	i;

	i = 1;
	while (av[i] != NULL)
	{
		if (ft_strchr(av[i], '=') != NULL)
		{
			if (ft_setenv(av[i], &info->_envp, &info->_mem) == NULL)
				return (perror("minishell : export :"), 1); // TODO : write malloc perror here
		}
		i++;
	}
	return (0);
}

static int	sb_unset(char **av, t_main *info)
{
	size_t	i;

	i = 1;
	while (av[i] != NULL)
	{
		if (ft_unsetenv(av[i], &info->_envp, &info->_mem) == NULL)
			return (perror("minishell : export :"), 1); // TODO : write perror here
		i++;
	}
	return (0);
}

/*
RETURN VALUE
-1			: cmd isn't built-in
0			: no error
positive	: error
*/

int	tun_builin_handler(char *cmd, char **av, t_main *info)
{
	size_t	size;
	int		err;

	err = -1;
	size = ft_strlen(cmd);
	if (ft_strncmp(cmd, "echo", size) == 0)
		err = sb_echo(av);
	else if (ft_strncmp(cmd, "pwd", size) == 0)
		err = 0 & printf("%s\n", info->_path);
	else if (ft_strncmp(cmd, "cd", size) == 0)
		err = sb_cd(av, info);
	else if (ft_strncmp(cmd, "export", size) == 0)
		err = sb_export(av, info);
	else if (ft_strncmp(cmd, "unset", size) == 0)
		err = sb_unset(av, info);
	else if (ft_strncmp(cmd, "exit", size) == 0)
		tun_builtin_exit(av, &info->_mem);
	return (err);
}