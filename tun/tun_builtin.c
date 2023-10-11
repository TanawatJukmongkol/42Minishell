/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/11 20:28:33 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

// WORK

// static int	sb_echo(char **av, t_exec *exe)
// {
// 	size_t	len;
// 	int		i;
// 	int		flag;

// 	if (av[1] == NULL)
// 		return (0);
// 	len = ft_strlen(av[1]);
// 	flag = ft_strncmp(av[1], "-n", len + 1);
// 	i = ft_ternary(flag == 0, 2, 1);
// 	while (av[i] != NULL)
// 	{
// 		if (ft_strncmp(av[i], "$?", 2) == 0)
// 		{
// 			printf("%d%s", exe->_info->_ngong, &av[i][2]);
// 		}
// 		printf("%s", av[i]);
// 		if (av[i + 1] != NULL)
// 			printf(" ");
// 		i++;
// 	}
// 	if (flag != 0)
// 		printf("\n");
// 	return (0);
// }

// WORk

static int	sb_cd(char **av, t_main *info)
{
	int		err;
	char	*err_str;
	char	*home;

	if (av[1] == NULL)
	{
		home = ft_getenv(&info->_envp, "HOME");
		if (home == NULL)
		{
			err_str = "minishell: cd: HOME not set";
			write(STDERR_FILENO, err_str, ft_strlen(err_str));
			return (1);
		}
	}
	if (av[2] != NULL)
	{
		err_str = "minishell: cd: too many arguments";
		write(STDERR_FILENO, err_str, ft_strlen(err_str));
		return (1);
	}
	err = ft_chdir(av[1], info);
	if (err != 0)
		perror(""); // TODO : write here
	return (err);
}

// WORK

static int	sb_export(char **av, t_main *info)
{
	size_t	i;

	i = 1;
	while (av[i] != NULL)
	{
		if (ft_strchr(av[i], '=') != NULL)
		{
			if (ft_setenv(av[i], &info->_envp) == NULL)
			{
				perror("minishell : export :");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

// WORK

static int	sb_unset(char **av, t_main *info)
{
	size_t	i;

	i = 1;
	while (av[i] != NULL)
	{
		if (ft_unsetenv(av[i], &info->_envp) == NULL)
		{
			perror("minishell : unset :");
			return (1);
		}
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

int	tun_builin_handler(char *cmd, char **av, t_exec *exe)
{
	size_t	size;
	int		err;
	char	*curr;

	err = -1;
	size = ft_strlen(cmd);
	if (ft_strncmp(cmd, "echo", size) == 0)
		err = tun_echo(av, exe);
	else if (ft_strncmp(cmd, "pwd", size) == 0)
	{
		curr = ft_getcwd();
		if (curr == NULL)
			return (ENOMEM);
		err = 0 & printf("%s\n", curr);
		free(curr);
	}
	else if (ft_strncmp(cmd, "cd", size) == 0)
		err = sb_cd(av, exe->_info);
	else if (ft_strncmp(cmd, "export", size) == 0)
		err = sb_export(av, exe->_info);
	else if (ft_strncmp(cmd, "unset", size) == 0)
		err = sb_unset(av, exe->_info);
	else if (ft_strncmp(cmd, "exit", size) == 0)
		tun_builtin_exit(exe, av);
	return (err);
}