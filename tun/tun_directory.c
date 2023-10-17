/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_directory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/17 18:20:03 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

static int	sb_no_arg(t_main *info)
{
	int		err;
	char	*err_str;
	char	*home;

	home = ft_getenv(&info->_envp, "HOME");
	if (home == NULL)
	{
		err_str = "minishell: cd: HOME not set";
		write(STDERR_FILENO, err_str, ft_strlen(err_str));
		return (1);
	}
	err = ft_chdir(home, info);
	if (err != 0)
		tun_file_perror("minishell: cd:", home);
	return (err);
}

int	tun_cd(char **av, t_main *info)
{
	int		err;
	char	*err_str;

	if (av[1] == NULL)
		return (sb_no_arg(info));
	else if (av[2] != NULL)
	{
		err_str = "minishell: cd: too many arguments";
		write(STDERR_FILENO, err_str, ft_strlen(err_str));
		return (1);
	}
	err = ft_chdir(av[1], info);
	if (err != 0)
		tun_file_perror("minishell: cd: ", av[1]);
	return (err);
}

int	tun_pwd(void)
{
	char	*curr;

	curr = ft_getcwd();
	if (curr == NULL)
		return (1);
	printf("%s\n", curr);
	free(curr);
	return (0);
}
