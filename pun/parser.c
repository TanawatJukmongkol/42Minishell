/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:46:42 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/12 14:46:24 by Tanawat J.       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pun.h"
#include <threads.h>

void	init_table(t_cmd_table *table)
{
	table->cmd = NULL;
	table->search_argv = 0;
	table->infile.begin = NULL;
	table->infile.last = NULL;
	table->outfile.begin = NULL;
	table->outfile.last = NULL;
	table->argv.begin = NULL;
	table->argv.last = NULL;
}

void	rm_next(t_token *t)
{
	t_token	*tmp;

	if (!t->next)
		return ;
	tmp = t->next;
	t->next = t->next->next;
	free(tmp->value);
	free(tmp);
}

void	build_table(t_token_stream *s, t_cmd_table *table, int pipe)
{
	t_token *cmd;

	cmd = ft_token(s, __cmd);
	cmd->value = table->cmd;
	if (table->argv.begin)
	{
		s->last->next = table->argv.begin;
		s->last = table->argv.last;
	}
	if (table->infile.begin)
	{
		if (!s->begin)
		{
			s->begin = table->infile.begin;
			s->last = table->infile.last;
		}
		s->last->next = table->infile.begin;
		s->last = table->infile.last;
	}
	if (table->outfile.begin)
	{
		if (!s->begin)
		{
			s->begin = table->outfile.begin;
			s->last = table->outfile.last;
		}
		s->last->next = table->outfile.begin;
		s->last = table->outfile.last;
	}
	if (pipe)
		ft_token(s, __pipe)->value = ft_strdup("|");
	if (!cmd->value)
	{
		s->begin = cmd->next;
		free(cmd);
	}
	init_table(table);
}

void	cmdtable_switch(t_token_stream *s, t_token *t, void *vars)
{
	t_cmd_table	*table;

	table = (t_cmd_table *)vars;
	if (t->type == __none)
	{
		if (table->search_argv)
			ft_token(&table->argv, __argv)->value = ft_strdup(t->value);
		else
		{
			table->cmd = ft_strdup(t->value);
			table->search_argv = 1;
		}
	}
	if (t->next)
	{
		if (t->type == __redirr_in || t->type == __here_doc)
		{
			ft_token(&table->infile, t->type)->value = ft_strdup(t->next->value);
			rm_next(t);
		}
		if (t->type == __redirr_append || t->type == __redirr_trunc)
		{
			ft_token(&table->outfile, t->type)->value = ft_strdup(t->next->value);
			rm_next(t);
		}
	}
	if (!t->next)
		return (build_table(s, table, 0));
	if (t->type == __pipe)
		return (build_table(s, table, 1));
}

void	parser(t_token_stream *output, t_token_stream *input)
{
	t_cmd_table	cmd_table;

	init_table(&cmd_table);
	while (input->begin)
		ft_token_consume(output, input, cmdtable_switch, &cmd_table);
}

