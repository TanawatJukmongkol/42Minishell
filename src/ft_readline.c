/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 16:04:49 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/17 19:49:18 by Tanawat J.       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

char	*ft_readline(const char *prompt, t_stackheap *mem)
{
	char	*ln;
	char	*tmp;

	ln = readline(prompt);
	if (ln == NULL || ft_strlen(ln) == 0)
		return (NULL);
	add_history(ln);
	tmp = ft_strtrim_heap(ln, "\n", mem);
	free(ln);
	return (tmp);
}
