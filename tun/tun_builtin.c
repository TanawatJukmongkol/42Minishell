/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/17 23:53:24 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

// WORk

// static int	sb_cd(char **av, t_main *info)
// {
// 	int		err;
// 	char	*err_str;
// 	char	*home;

// 	if (av[1] == NULL)
// 	{
// 		home = ft_getenv(&info->_envp, "HOME");
// 		if (home == NULL)
// 		{
// 			err_str = "minishell: cd: HOME not set";
// 			write(STDERR_FILENO, err_str, ft_strlen(err_str));
// 			return (1);
// 		}
// 		err = ft_chdir(home, info);
// 		if (err != 0)
// 			tun_file_perror("minishell: cd: ", home);
// 		return (err);
// 	}
// 	else if (av[2] != NULL)
// 	{
// 		err_str = "minishell: cd: too many arguments";
// 		write(STDERR_FILENO, err_str, ft_strlen(err_str));
// 		return (1);
// 	}
// 	err = ft_chdir(av[1], info);
// 	if (err != 0)
// 		tun_file_perror("minishell: cd: ", av[1]);
// 	return (err);
// }

// WORK

static int	sb_export(char **av, t_main *info)
{
	size_t	i;

	i = 0;
	if (av[1] == NULL)
	{
		ft_sorttable(info->_envp.env);
		while (info->_envp.env[i])
		{
			printf("declare -x %s\n", info->_envp.env[i]);
			i++;
		}
	}
	while (av[++i] != NULL)
	{
		if (ft_strchr(av[i], '=') != NULL)
		{
			if (ft_setenv(av[i], &info->_envp) == NULL)
			{
				perror("minishell : export :");
				return (1);
			}
		}
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

// exit, export, unset, cd

int	tun_builtin_parent(t_token_stream *box, pid_t *pid, t_exec *exe, size_t n)
{
	size_t	size;
	int		err;

	err = -1;
	if (exe->argv[0] == NULL)
		return (-1);
	size = ft_strlen(exe->argv[0]);
	if (ft_strncmp(exe->argv[0], "cd", size) == 0)
		err = tun_cd(exe->argv, exe->_info);
	else if (ft_strncmp(exe->argv[0], "export", size) == 0)
		err = sb_export(exe->argv, exe->_info);
	else if (ft_strncmp(exe->argv[0], "unset", size) == 0)
		err = sb_unset(exe->argv, exe->_info);
	else if (ft_strncmp(exe->argv[0], "exit", size) == 0)
		tun_builtin_exit(box, pid, exe, n);
	if (err >= 0)
		exe->_info->_ngong = err;
	return (err);
}

// echo, pwd

int	tun_builtin_child(t_exec *exe)
{
	size_t	size;
	int		err;

	err = -1;
	if (exe->argv[0] == NULL)
		return (-1);
	size = ft_strlen(exe->argv[0]);
	if (ft_strncmp(exe->argv[0], "echo", size) == 0)
		err = tun_echo(exe->argv, exe);
	else if (ft_strncmp(exe->argv[0], "pwd", size) == 0)
		err = tun_pwd();
	if (err >= 0)
		exe->_info->_ngong = err;
	return (err);
}

// int	tun_isbuiltin(char *cmd)
// {
// 	size_t	size;

// 	size = ft_strlen(cmd);
// 	if (ft_strncmp("cd", cmd, size) == 0)
// 		return (1);
// 	else if (ft_strncmp("pwd", cmd, size) == 0)
// 		return (1);
// 	else if (ft_strncmp("echo", cmd, size) == 0)
// 		return (1);
// 	else if (ft_strncmp("export", cmd, size) == 0)
// 		return (1);
// 	else if (ft_strncmp("unset", cmd, size) == 0)
// 		return (1);
// 	else if (ft_strncmp("echo", cmd, size) == 0)
// 		return (1);
// 	return (0);
// }
