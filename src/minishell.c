/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:00:31 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/12 14:38:09 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_token_stream	lex;
	t_token_stream	*box;
	t_main			info;
	size_t			pipe_n;
	char			*line;

	(void)av;
	if (ac != 1)
		return (0);
	if (ft_init_main(&info, envp) == -1)
		return (ENOMEM);
	lex.begin = NULL;
	lex.last = NULL;
	line = ft_readline("minishell>");
	while (line != NULL)
	{
		if (line[0] != 0)
		{
			lexer(&lex, line);
			parser(&info._token, &lex);
			if (info._token.begin == NULL)
				return (ft_clear_main(&info, 0));
			box = tun_split_token(&info, &pipe_n);
			tun_parent_process(&info, box, pipe_n);
			tun_free_token_box(box, pipe_n);
		}
		else
			free(line);
		line = ft_readline("minishell>");
	}
	return (ft_clear_main(&info, 0));
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_stackheap		mem;
// 	char			*prompt;
// 	char			*line;
// 	t_token_stream	stream;
// 	t_token_stream	output;

// 	(void)(argc);
// 	(void)(argv);
// 	(void)(envp);
// 	heap_init(&mem);
// 	stream.begin = NULL;
// 	output.begin = NULL;
// 	while (1)
// 	{
// 		char	*cwd = ft_getcwd(&mem);
// 		prompt = ft_strjoin(cwd, "> ");
// 		free(cwd);
// 		line = ft_readline(prompt);
// 		free(prompt);
// 		if (!line || !*line)
// 			continue ;
// 		lexer(&stream, line);
// 		parser(&output, &stream);

// 		// output = stream;
// 		for (t_token *i=output.begin; i; i = i->next)
// 		{
// 			switch (i->type)
// 			{
// 				case __none:
// 					printf("%-14s", "none"); break;
// 				case __pipe:
// 					printf("%-14s", "pipe"); break;
// 				case __redirr_in:
// 					printf("%-14s", "redirr_in"); break;
// 				case __here_doc:
// 					printf("%-14s", "here_doc"); break;
// 				case __redirr_trunc:
// 					printf("%-14s", "redirr_trunc"); break;
// 				case __redirr_append:
// 					printf("%-14s", "redirr_append"); break;
// 				case __cmd:
// 					printf("%-14s", "cmd"); break;
// 				case __argv:
// 					printf("%-14s", "argv"); break;
// 			}
// 			printf("-> %s\n", i->value);
// 		}
// 		// ft_tokenfree(&stream);
// 		ft_tokenfree(&output);
// 	}
// 	return (0);
// }

// OUTPUT EMULATOR

// void	set_node(t_token_stream *output, t_token_type num, char *val)
// {
// 	t_token	*node;

// 	node = malloc(sizeof(t_token));
// 	node->value = val;
// 	node->type = num;
// 	node->next = NULL;
// 	if (output->begin == NULL)
// 	{
// 		output->begin = node;
// 		output->last = node;
// 	}
// 	else
// 	{
// 		output->last->next = node;
// 		output->last = node;
// 	}
// }

// void	set_output(t_token_stream *output, char *list[], t_token_type *num)
// {
// 	int		i = 0;

// 	output->begin = NULL;
// 	output->last = NULL;
// 	while (list[i] != NULL)
// 	{
// 		set_node(output, num[i], list[i]);
// 		i++;
// 	}
// }

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
/*
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
*/
