/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 16:04:49 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/04 12:18:26 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

char	*ft_readline(const char *prompt)
{
	char	*ln;
	char	*tmp;

	ln = readline(prompt);
	if (ln == NULL)
		return (NULL);
	add_history(ln);
	tmp = ft_strtrim(ln, "\n");
	free(ln);
	return (tmp);
}
