/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:46:42 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/13 13:45:37 by tjukmong         ###   ########.fr       */
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
	table->argv.begin = NULL;
	table->search_argv = 0;
	table->indx = 0;
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
	if (table->infile)
		ft_token(s, __redirr_in)->value = table->infile;
	if (table->outfile)
	{
		if (table->trunc)
			ft_token(s, __redirr_trunc)->value = table->outfile;
		else
			ft_token(s, __redirr_append)->value = table->outfile;
	}
	clear_cmd_table(table);
}

char	*set_cmd_table(t_token *t)
{
	t_token	*tmp;
	char	*val;

	val = ft_strdup(t->next->value);
	tmp = t->next;
	t->next = t->next->next;
	free(tmp->value);
	free(tmp);
	return (val);
}

void	cmdtable_switch(t_token_stream *s, t_token *t, void *vars)
{
	t_cmd_table	*table;

	table = (t_cmd_table *)vars;
	if (table->search_argv && t->type == __none)
		ft_token(&table->argv, __argv)->value = ft_strdup(t->value);
	if (t->next)
	{
		if (t->type == __here_doc)
			table->here_doc = set_cmd_table(t);
		if (t->type == __redirr_in)
			table->infile = set_cmd_table(t);
		if (t->type == __redirr_append)
		{
			table->outfile = set_cmd_table(t);
			table->trunc = 0;
		}
		if (t->type == __redirr_trunc)
		{
			table->outfile = set_cmd_table(t);
			table->trunc = 1;
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
