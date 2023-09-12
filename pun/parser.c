/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:46:42 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/13 06:44:40 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pun.h"

void	clear_cmd_table(t_cmd_table *table)
{
	table->cmd = NULL;
	table->here_doc = NULL;
	table->infile = NULL;
	table->outfile = NULL;
	table->trunc = 0;
	table->indx = 0;
}

void	build_stream_from_table(t_cmd_table *table)
{
	printf("cmd: %s\n", table->cmd);
	printf("here_doc: %s\n", table->here_doc);
	printf("infile: %s\n", table->infile);
	printf("outfile: %s\n", table->outfile);
	printf("trunc? : %d\n", table->trunc);
	clear_cmd_table(table);
}

void	cmdtable_switch(t_token_stream *s, t_token *t, void *vars)
{
	t_cmd_table	*table;

	table = (t_cmd_table *)vars;
	(void)(s);
	(void)(t);
	(void)(vars);

	if (table->search_argv && t->type == __none)
		ft_token(s, __argv)->value = ft_strdup(t->value);
	if (t->next)
	{
		if (t->type == __here_doc)
		{
			table->here_doc = ft_strdup(t->next->value);
			t->next = t->next->next;
		}
		if (t->type == __redirr_in)
		{
			table->infile = ft_strdup(t->next->value);
			t->next = t->next->next;
		}
	}
	if (t->type == __none && !table->search_argv)
	{
		table->cmd = ft_strdup(t->value);
		table->search_argv = 1;
	}
	if (table->search_argv && t->type != __none)
		table->search_argv = 0;
	table->indx++;
	if (t->type == __pipe || t->next == NULL)
		build_stream_from_table(table);
}

void	parser(t_token_stream *output, t_token_stream *input)
{
	t_cmd_table		cmd_table;
	// t_token_stream	stage1;
	//t_token_stream	stage2;

	clear_cmd_table(&cmd_table);
	// stage1.begin = NULL;
	//stage2.begin = NULL;
	while (input->begin)
		ft_token_consume(output, input, cmdtable_switch, &cmd_table);
}
