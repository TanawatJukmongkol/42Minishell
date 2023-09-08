/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 16:04:49 by tjukmong          #+#    #+#             */
/*   Updated: 2023/08/21 15:08:19 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

char	*ft_readline(const char *prompt)
{
	char	*ln;
	char	*tmp;

	ln = readline(prompt);
	add_history(ln);
	tmp = ft_strtrim(ln, "\n");
	free(ln);
	return (tmp);
}
