/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/14 03:23:00 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

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
		err = ft_chdir(home, info);
		if (err != 0)
			perror("minishell: cd");
		return (err);
	}
	else if (av[2] != NULL)
	{
		err_str = "minishell: cd: too many arguments";
		write(STDERR_FILENO, err_str, ft_strlen(err_str));
		return (1);
	}
	err = ft_chdir(av[1], info);
	if (err != 0)
		perror("minishell: cd");
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

static int	sb_pwd(void)
{
	char	*curr;

	curr = ft_getcwd();
	if (curr == NULL)
		return (ENOMEM);
	printf("%s\n", curr);
	free(curr);
	return (0);
}

/*
RETURN VALUE
-1			: cmd isn't built-in
0			: no error
positive	: error
*/

int	tun_builin_handler(t_token_stream *box, int *pid, t_exec *exe, int e)
{
	size_t	size;
	int		err;

	err = -1;
	if (exe->argv[0] == NULL || e == 0)
		return (0);
	size = ft_strlen(exe->argv[0]);
	if (ft_strncmp(exe->argv[0], "echo", size) == 0)
		err = tun_echo(exe->argv, exe);
	else if (ft_strncmp(exe->argv[0], "pwd", size) == 0)
		err = sb_pwd();
	else if (ft_strncmp(exe->argv[0], "cd", size) == 0)
		err = sb_cd(exe->argv, exe->_info);
	else if (ft_strncmp(exe->argv[0], "export", size) == 0)
		err = sb_export(exe->argv, exe->_info);
	else if (ft_strncmp(exe->argv[0], "unset", size) == 0)
		err = sb_unset(exe->argv, exe->_info);
	else if (ft_strncmp(exe->argv[0], "exit", size) == 0)
		tun_builtin_exit(box, pid, exe);
	if (err >= 0)
		exe->_info->_ngong = err;
	return (err);
}