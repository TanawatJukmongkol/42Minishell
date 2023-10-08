/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_get_argv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/05 18:28:31 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

int	tun_count_type(t_token_stream *subset, t_token_type t1, t_token_type t2)
{
	int		len;
	t_token	*run;

	len = 0;
	run = subset->begin;
	while (run != NULL)
	{
		len += (run->type == t1 || run->type == t2);
		run = run->next;
	}
	return (len);
}

char	**tun_get_argv(t_token_stream *subset, t_main *info)
{
	int		i;
	int		len;
	t_token	*run;
	char	**argv;

	(void)info;
	len = tun_count_type(subset, __cmd, __argv);
	argv = malloc(sizeof(char *) * (len + 1));
	if (argv == NULL)
		return (NULL);
	run = subset->begin;
	i = 0;
	while (run != NULL && i < len)
	{		
		if (run->type == __cmd || run->type == __argv)
		{
			argv[i] = ft_strdup(run->value);
			if (argv[i] == NULL)
				return (ft_free_split(argv), NULL);
			i++;
		}
		run = run->next;
	}
	argv[i] = NULL;
	return (argv);
}