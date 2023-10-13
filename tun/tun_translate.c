/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_get_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 02:08:33 by tponutha          #+#    #+#             */
/*   Updated: 2023/10/14 02:10:43 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

int	tun_get_infile(t_token_stream subset, t_exec *exe)
{
	int	i;
	int	j;
	int	err;

	i = 1;
	j = 0;
	err = 1;
	if (exe->in_len == 0)
		return (err);
	exe->infile[0] = STDIN_FILENO;
	while (subset.begin != NULL && err == 1 && errno != ENOMEM && i < exe->in_len)
	{
		if (subset.begin->type == __redirr_in)
		{
			exe->infile[i] = tun_open(subset.begin->value, O_RDONLY, 0644);
			err = exe->infile[i] != -1;
		}
		else if (subset.begin->type == __here_doc)
		{
			exe->infile[i] = STDIN_FILENO;
			exe->delimeter[j] = subset.begin->value;
			j++;
		}
		i += subset.begin->type == __redirr_in \
			|| subset.begin->type == __here_doc;
		subset.begin = subset.begin->next;
	}
	exe->delimeter[j] = NULL;
	return (err);
}

int	tun_get_outfile(t_token_stream subset, t_exec *exe)
{
	int	i;
	int	err;

	i = 1;
	err = 1;
	if (exe->out_len == 0)
		return (err);
	exe->outfile[0] = STDOUT_FILENO;
	while (subset.begin != NULL && err == 1 && errno != ENOMEM && i < exe->out_len)
	{
		if (subset.begin->type == __redirr_append)
		{
			exe->outfile[i] = tun_open(subset.begin->value, \
								O_WRONLY | O_APPEND | O_CREAT, 0644);
			err = exe->outfile[i] != -1;
		}
		else if (subset.begin->type == __redirr_trunc)
		{
			exe->outfile[i] = tun_open(subset.begin->value, \
								O_WRONLY | O_TRUNC | O_CREAT, 0644);
			err = exe->outfile[i] != -1;
		}
		i += subset.begin->type == __redirr_append \
			|| subset.begin->type == __redirr_trunc;
		subset.begin = subset.begin->next;
	}
	return (err);
}

void	tun_get_argv(t_token_stream subset, t_exec *exe)
{
	int		i;

	i = 0;
	while (subset.begin != NULL && exe->argv[i] != NULL)
	{		
		if (subset.begin->type == __cmd || subset.begin->type == __argv)
		{
			exe->argv[i] = subset.begin->value;
			i++;
		}
		subset.begin = subset.begin->next;
	}
	exe->argv[i] = NULL;
}