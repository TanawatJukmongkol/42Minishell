/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 16:04:49 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/12 14:40:49 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

char	*ft_readline(const char *prompt)
{
	char	*ln;

	ln = readline(prompt);
	if (ln == NULL)
		return (NULL);
	if (ln[0] == 0)
		return (ln);
	add_history(ln);
	return (ln);
}
