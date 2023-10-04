/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:00:31 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/04 21:08:06 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	main(int ac, char **av, char **envp)
// {
// 	t_token_stream	lex;
// 	t_main			info;
// 	char			*line;

// 	(void)av;
// 	if (ac != 1)
// 		return (0);
// 	if (ft_init_main(&info, envp) == -1)
// 	{
// 		heap_purge(&info._mem);
// 		return (ENOMEM);
// 	}
// 	lex.begin = NULL;
// 	lex.last = NULL;
// 	line = ft_readline("minishell>");	// use readkine
// 	while (line != NULL)
// 	{
// 		lexer(&lex, line);
// 		parser(&info._token, &lex);
// 		while (info._token.begin != NULL)
// 		{
// 			printf("%d - %s\n", info._token.begin->type, info._token.begin->value);
// 			info._token.begin = info._token.begin->next;
// 		}
// 		// heap_free(&info._mem, line);
// 		line = ft_readline("minishell>");	
// 	}
// 	heap_purge(&info._mem);
// 	return (0);
// }

// OUTPUT EMULATOR

void	set_node(t_token_stream *output, t_token_type num, char *val)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	node->value = val;
	node->type = num;
	node->next = NULL;
	if (output->begin == NULL)
	{
		output->begin = node;
		output->last = node;
	}
	else
	{
		output->last->next = node;
		output->last = node;
	}
}

void	set_output(t_token_stream *output, char *list[], t_token_type *num)
{
	int		i = 0;

	output->begin = NULL;
	output->last = NULL;
	while (list[i] != NULL)
	{
		set_node(output, num[i], list[i]);
		i++;
	}
}

// int	main(int ac, char **av, char **envp)
// {
// 	char	*list[] = {"cat", "infile", "|", "ls", "-l", "-a", "|", "sleep", "5", "env", "|", "grep", "PATH", NULL};
// 	t_token_type	num[] = {__cmd, __redirr_in, __pipe, __cmd, __argv, __argv, __pipe, __cmd, __argv, __pipe, __cmd, __argv, __none};
// 	t_main			info;
// 	t_token_stream	*box;
// 	t_token_stream	*run;
// 	size_t			pipe_n;
// 	size_t			i;

// 	(void)av;
// 	if (ac != 1)
// 		return (0);
// 	ft_init_main(&info, envp);
// 	set_output(&info._token, list, num);
// 	while (i < pipe_n + 1)
// 	{
// 		run = &box[i];
// 		while (run->begin != NULL)
// 		{
// 			printf("%s (type:%d)\n", run->begin->value, run->begin->type);
// 			run->begin = run->begin->next;
// 		}
// 		i++;
// 	}
// 	// heap_purge(&info._mem);
// 	return (0);
// }

int	main(int ac, char **av, char **envp)
{
	char	*list[] = {"cat", "infile", "|", "ls", "-l", "-a", "|", "sleep", "|", "env", "|", "grep", "PATH", NULL};
	t_token_type	num[] = {__cmd, __redirr_in, __pipe, __cmd, __argv, __argv, __pipe, __cmd, __pipe, __cmd, __pipe,  __cmd, __argv, __none};
	t_main			info;

	(void)av;
	if (ac != 1)
		return (0);
	ft_init_main(&info, envp);
	set_output(&info._token, list, num);
	tun_parent_process(&info);
	ft_tokenfree(&info._token);
	heap_purge(&info._mem);
	return (0);
}