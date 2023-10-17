/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_builtin_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/18 04:00:49 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

/*
0 : success
1: file permission denied
126: cmd permission denied
127: no such file or directory
*/

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

	i = ft_isdigit(num[0]) == 0;
	if (num[0] != '+' && num[0] != '-' && ft_isdigit(num[0]) == 0)
		return (1);
	while (num[i] != 0)
	{
		if (ft_isdigit(num[i]) == 0)
			return (1);
		i++;
	}
	*e = sb_atol(num, &overflow);
	return (overflow);
}

static void	sb_exit_error(char *str)
{
	char	*front;
	char	*back;
	char	*first;
	char	*res;

	front = "minishell: exit: ";
	back = ": numeric argument required\n";
	first = ft_strjoin(front, str);
	if (first != NULL)
		res = ft_strjoin(first, back);
	if (first != NULL && back != NULL)
	{
		write(STDERR_FILENO, res, ft_strlen(res));
		free(first);
		free(res);
	}
	else
		perror("minishell: exit:");
}

static void	sb_val_exit(int val, t_exec *exe, t_token_stream *box, size_t n)
{
	tun_close_pipe(&exe->_pipes);
	tun_clear_process(exe);
	tun_free_token_box(box, n);
	exit(val);
}

// TODO : handle free too

void	tun_builtin_exit(t_token_stream *box, pid_t *pid, t_exec *exe, size_t n)
{
	size_t			len;
	unsigned char	e;
	char			*msg;

	len = 0;
	msg = "minishell: exit: too many arguments\n";
	while (exe->argv[len] != NULL && len <= 2)
		len++;
	if (len > 2)
		return ((void)write(2, msg, ft_strlen(msg)));
	if (len == 1)
	{
		free(pid);
		if (n == 0)
			printf("exit\n");
		sb_val_exit(0, exe, box, n);
	}
	if (n == 0)
		printf("exit\n");
	if (sb_check_number(exe->argv[1], &e))
		sb_exit_error(exe->argv[1]);
	sb_val_exit(e, exe, box, n);
}
