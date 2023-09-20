/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:46:42 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/17 20:18:24 by Tanawat J.       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pun.h"

void	clear_cmd_table(t_cmd_table *table)
{
	table->cmd = NULL;
	table->here_doc = NULL;
	table->search_argv = 0;
	table->indx = 0;
	table->infile.begin = NULL;
	table->outfile.begin = NULL;
	table->argv.begin = NULL;
}

void	build_stream_from_table(t_token_stream *s, t_cmd_table *table)
{
	if (table->cmd)
		ft_token(s, __cmd)->value = table->cmd;
	if (table->argv.begin)
	{
		s->last->next = table->argv.begin;
		s->last = table->argv.last;
	}
	if (table->here_doc)
		ft_token(s, __here_doc)->value = table->here_doc;
	if (table->infile.begin)
	{
		s->last->next = table->infile.begin;
		s->last = table->infile.last;
	}
	if (table->outfile.begin)
	{
		s->last->next = table->outfile.begin;
		s->last = table->outfile.last;
	}
	clear_cmd_table(table);
}

void	rm_next(t_token *t)
{
	t_token	*tmp;

	tmp = t->next;
	t->next = t->next->next;
	free(tmp->value);
	free(tmp);
}

char	*set_cmd_table(t_token *t)
{
	char	*val;

	val = ft_strdup(t->next->value);
	rm_next(t);
	return (val);
}

void	cmdtable_switch(t_token_stream *s, t_token *t, void *vars)
{
	t_cmd_table	*table;

	table = (t_cmd_table *)vars;
	if (table->search_argv && t->type == __none)
		ft_token(&table->argv, __argv)->value = ft_strdup(t->value);
	if (t->next && t->next->type == __none)
	{
		if (t->type == __here_doc)
			table->here_doc = set_cmd_table(t);
		if (t->type == __redirr_in)
		{
			ft_token(&table->infile, __redirr_in)->value = ft_strdup(\
				t->next->value);
			rm_next(t);
		}
		if (t->type == __redirr_append)
		{
			ft_token(&table->outfile, __redirr_append)->value = ft_strdup(\
				t->next->value);
			rm_next(t);
		}
		if (t->type == __redirr_trunc)
		{
			ft_token(&table->outfile, __redirr_trunc)->value = ft_strdup(\
				t->next->value);
			rm_next(t);
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
	{
		build_stream_from_table(s, table);
		if (t->type == __pipe)
			ft_token(s, __pipe)->value = ft_strdup("|");
	}
}

void	parser(t_token_stream *output, t_token_stream *input)
{
	t_cmd_table		cmd_table;

	clear_cmd_table(&cmd_table);
	if (!output || !input)
		return ;
	while (input->begin)
		ft_token_consume(output, input, cmdtable_switch, &cmd_table);
}
