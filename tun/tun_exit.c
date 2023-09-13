/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/13 02:38:45 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

/*
0 : success
1: file permission denied
126: cmd permission denied
127: no such file or directory
*/

void	tun_child_exit(t_stackheap *mem, int isexe)
{
	if (errno == ENOENT)
		ft_exit(mem, 127);
	if (errno == EACCES)
	{
		if (isexe != -1)
			ft_exit(mem, 126);
		ft_exit(mem, 1);
	}
	ft_exit(mem, 0);
}

static long	sb_atol(char *str, int *overflow)
{
	long			num;
	long			neg;
	unsigned long	sum;

	if (!str)
		return (0);
	sum = 0;
	neg = 1;
	*overflow = 0;
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	if (*str == '-')
		neg = -1;
	str += (*str == '+' || *str == '-');
	while (ft_isdigit(*str) && *overflow != 1)
	{
		sum = (sum * 10) + (*str - '0');
		if (sum > (size_t)LONG_MAX + (size_t)(neg == -1))
			*overflow = 1;
		str++;
	}
	num = sum;
	return (neg * num);
}

// true if
// - num too long (num > LONG_MAX)
// - there is non number charactor
// - too much +, -

static int	sb_check_number(char *num, unsigned char *e)
{
	int		overflow;
	size_t	i;

	i = 0;
	while (num[i] != 0)
	{
		if (i == 0 && num[i] != '+' && num[i] != '-')
			return (1);
		else
		{
			if (ft_isdigit(num[i]) == 0)
				return (1);
		}
		i++;
	}
	*e = sb_atol(num, &overflow);
	return (*e != 1);
}

static void	sb_exit_error(char *str, t_stackheap *mem)
{
	char	*front;
	char	*back;
	char	*first;
	char	*res;

	front = "minishell: exit: ";
	back = ": numeric argument required";
	first = ft_strjoin_heap(front, str, mem);
	if (first != NULL)
		res = ft_strjoin_heap(first, back, mem);
	if (first != NULL && back != NULL)
	{
		write(STDERR_FILENO, res, ft_strlen(res));
		heap_free(mem, first);
		heap_free(mem, res);
	}
	else
		perror("minishell: exit:");
}

void	tun_builtin_exit(char **av, t_stackheap *mem)
{
	size_t			len;
	unsigned char	e;
	char			*msg;

	len = 0;
	msg = "minishell: exit: too many arguments";
	while (av[len] != NULL)
		len++;
	if (len != 2)
		return (void)write(2, msg, ft_strlen(msg)); // TODO : write perror here
	if (sb_check_number(av[1], &e))
		return (sb_exit_error(av[1], mem));
	printf("exit\n");
	ft_exit(mem, e);
}